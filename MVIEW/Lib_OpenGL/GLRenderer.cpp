#include "Plugin_Renderer_GL.h"
#include "GLError.h"




namespace mview {

	GLRenderer::GLRenderer(): m_cam(nullptr)
	{		
	}

	GLRenderer::GLRenderer(int width, int height):GLRenderer()
	{
		m_width = width;
		m_height = height;
		m_glSceneData.reset(new GLSceneData());
	}

	bool GLRenderer::Init()
	{
		//////////////////////////////////////// GL Stuff Initialization /////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Dark blue background
		gl_check_error();
		glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

		// Enable muti-sampling
		glEnable(GL_MULTISAMPLE);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		// Cull triangles which normal is not towards the camera
		glEnable(GL_CULL_FACE);

		
		gl_check_error();

		/****************************Drawing Data Initlization***********************/
		gl_check_error();
		std::string shaderFile = std::string("..\\Shaders\\Opengl\\");
		
		//shaderFile += "LightingShader.glsl";
		shaderFile += "SimpleShader.glsl";
		m_shader.reset(new GLShaderTechnique(shaderFile.c_str()));
		gl_check_error();		
		
		glGenBuffers(1, &m_ubo_InfoUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_InfoUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(m_uboInfoData), &m_uboInfoData, GL_DYNAMIC_DRAW);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		
		GLuint binding_point_index = UBOInfoData_BPI;
		glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, m_ubo_InfoUBO);
		gl_check_error();		
		

		//********** Setting up main grid for rendering
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		//********** Set up scene data (meshes, textures, shaders etc...)
		
		m_cam.reset( new GLCamera(SceneManager::getCam()));
		m_cam->BindToShaderNonIndexed(m_shader);
		/*m_meshObjectList = g_sceneController->getMeshObjectList();
		m_sceneObjects = g_sceneController->getSceneObjectList();
		m_lightList = g_sceneController->getLightList();*/
		//m_triMeshObjects.push_back(m_box->m_triangleMesh);
		return m_initialized = true;
	}

	bool GLRenderer::AddSceneData(const shrd_MObject object)
	{
		switch (object->m_type) {

		case MOBJECT_TYPE::TRIANGLE_MESH:
		{
			shrd_Model model = std::static_pointer_cast<Model>(object);
			
			//Important: Materials should be contigously populated for set of meshes belonging to 1 model so that they are removed correctly
			for (size_t i = 0; i < model->getTriMeshes().size(); i++) {
				shrd_GLTriangleMesh glTriMesh(new GLTriangleMesh(model->getTriMeshes()[i], model->m_id, model->getPose()));
				m_glSceneData->glTriMeshList.push_back(glTriMesh);
				
				for (size_t j = 0; j < TEXTURE_TYPE::TT_COUNT; j++)
				{
					if (model->getTriMeshes()[i]->m_textureIDs[j]) {
						glTriMesh->m_textures[j] = shrd_GLTexture(new GLTexture(model->getTriMeshes()[i]->m_textureIDs[j], model->GetTexLib()));						
					}
				}
				

				shrd_GLMaterial meshMaterial = shrd_GLMaterial(new GLMaterial(model->getTriMeshes()[i]->m_materialID, model->GetMatLib(), model->getTriMeshes()[i]->m_textureIDs));

				m_glSceneData->glMaterialList.push_back(meshMaterial);
				meshMaterial->BindToShader(m_shader, m_glSceneData->glMaterialList.size() - 1);
				glTriMesh->m_materialndex = m_glSceneData->glMaterialList.size() - 1;

				glTriMesh->m_renderMode = model->m_renderMode;

			}
					
			RefreshUBOCount(UBO_GLMATERIALS, m_glSceneData->glMaterialList.size());
			
			break;
		}

		case MOBJECT_TYPE::ZONE:
		{
			shrd_Zone zone = std::static_pointer_cast<Zone>(object);

					
			for (int i = 0; i < zone->getTerrainList().size(); i++) {
				switch (zone->getTerrainList()[i]->m_terrainType){
				case TT_GRID: {
					shrd_GLTerrain glTerrain(new GLTerrain(zone->getTerrainList()[i], zone->m_id, zone->getPose()));
					m_glSceneData->glTerrainList.push_back(glTerrain);
					break;
				}
				case TT_TRIMESH: {
					shrd_GLTriangleMesh glTriMesh(new GLTriangleMesh(zone->getTerrainList()[i], zone->m_id, zone->getPose()));
					m_glSceneData->glTriMeshList.push_back(glTriMesh);
					glTriMesh->m_renderMode = zone->m_renderMode;

					for (int j = 0; j < TEXTURE_TYPE::TT_COUNT; j++)
					{
						if (zone->getTerrainList()[i]->m_textureIDs[j]) {
							glTriMesh->m_textures[j] = shrd_GLTexture(new GLTexture(zone->getTerrainList()[i]->m_textureIDs[j], zone->GetTexLib()));
						}
					}

					shrd_GLMaterial meshMaterial = shrd_GLMaterial(new GLMaterial(zone->getTerrainList()[i]->m_materialID, zone->GetMatLib(), zone->getTerrainList()[i]->m_textureIDs));

					m_glSceneData->glMaterialList.push_back(meshMaterial);
					meshMaterial->BindToShader(m_shader, m_glSceneData->glMaterialList.size() - 1);
					glTriMesh->m_materialndex = m_glSceneData->glMaterialList.size() - 1;

					break;
				}
				default:
					break;
				}			

			}

			RefreshUBOCount(UBO_GLMATERIALS, m_glSceneData->glMaterialList.size());

			break;
		}

		case MOBJECT_TYPE::POINTLIGHT:
		{
			shrd_PointLight pointLight = std::static_pointer_cast<PointLight>(object);
			shrd_GLPointLight glPointLight(new GLPointLight(pointLight));
			m_glSceneData->glPointLightList.push_back(glPointLight);
			glPointLight->BindToShader(m_shader, m_glSceneData->glPointLightList.size() - 1);
			RefreshUBOCount(UBO_GLPOINTLIGHT, m_glSceneData->glPointLightList.size());
			shrd_GLTriangleMesh glTriMesh(new GLTriangleMesh(pointLight->getTriMeshes().at(0), pointLight->m_id, pointLight->getPose()));
			glTriMesh->m_renderMode = pointLight->m_renderMode;
			m_glSceneData->glTriMeshList.push_back(glTriMesh);			
			break;
		}

		default:
			break;
		}
		return true;
	}

	bool GLRenderer::ReplaceSceneData(const shrd_MObject object)
	{
		switch (object->m_type) {

		case MOBJECT_TYPE::TRIANGLE_MESH:
		{
			shrd_Model meshObj = std::static_pointer_cast<Model>(object);
			shrd_GLTriangleMesh glTriMesh(new GLTriangleMesh(meshObj->getTriMeshes().at(0), meshObj->m_id, meshObj->getPose()));
			std::replace_if(m_glSceneData->glTriMeshList.begin(), m_glSceneData->glTriMeshList.end(), CompareGLTrianlgeMesh(meshObj->m_id), glTriMesh);


			break;
		}

		case MOBJECT_TYPE::POINTLIGHT:
		{
			shrd_PointLight pointLight = std::static_pointer_cast<PointLight>(object);
			shrd_GLPointLight glPointLight(new GLPointLight(pointLight));
			std::replace_if(m_glSceneData->glPointLightList.begin(), m_glSceneData->glPointLightList.end(), CompareGLPointLight(pointLight->m_id), glPointLight);
			shrd_GLTriangleMesh glTriMesh(new GLTriangleMesh(pointLight->getTriMeshes().at(0), pointLight->m_id, pointLight->getPose()));
			std::replace_if(m_glSceneData->glTriMeshList.begin(), m_glSceneData->glTriMeshList.end(), CompareGLTrianlgeMesh(pointLight->m_id), glTriMesh);
			break;			
		}

		default:
			break;
		}
		return true;
	}

	void GLRenderer::ChangeSceneDataParam(const shrd_MObject object, int param)
	{
		if (object) {
			switch (object->m_type) {

			case MOBJECT_TYPE::TRIANGLE_MESH:
			{
				break;
			}

			case MOBJECT_TYPE::POINTLIGHT:
			{
				shrd_PointLight pointLight = std::static_pointer_cast<PointLight>(object);
				std::vector<shrd_GLPointLight>::iterator GLPointLightListitr = std::find_if(m_glSceneData->glPointLightList.begin(), m_glSceneData->glPointLightList.end(), CompareGLPointLight(pointLight->m_id));
				if (*GLPointLightListitr)
					(*GLPointLightListitr)->UpdateParam(param);
				break;
			}

			case MOBJECT_TYPE::CAMERA:
			{
				//shrd_Camera camra = std::static_pointer_cast<Camera>(object);
				m_cam->UpdateParam(param);
				break;
			}
			default:
				break;
			}
		}
	}

	bool GLRenderer::RemoveSceneData(const shrd_MObject object)
	{
		switch (object->m_type) {

		case MOBJECT_TYPE::TRIANGLE_MESH:
		{
			shrd_Model meshObj = std::static_pointer_cast<Model>(object);
			std::vector<int> materialIndices;
			std::vector<int> removedMeshIndices;
			for (int i = 0; i < meshObj->getTriMeshes().size(); i++) {
				std::vector<shrd_GLTriangleMesh>::iterator itr = std::find_if(m_glSceneData->glTriMeshList.begin(), m_glSceneData->glTriMeshList.end(), CompareGLTrianlgeMesh(meshObj->m_id));


				if (itr != m_glSceneData->glTriMeshList.end())
				{
					materialIndices.push_back((int)itr->get()->m_materialndex);
					removedMeshIndices.push_back((int)(itr - m_glSceneData->glTriMeshList.begin()));					
					m_glSceneData->glTriMeshList.erase(itr);
				}
				
			}

			//for (int i = 0; i < materialIndices.size(); i++)
			{
				std::vector<shrd_GLMaterial>::iterator mat_itrBegin = m_glSceneData->glMaterialList.begin() + materialIndices.at(0);
				std::vector<shrd_GLMaterial>::iterator mat_itrEnd = m_glSceneData->glMaterialList.begin() + materialIndices.at(materialIndices.size()-1);
				m_glSceneData->glMaterialList.erase(mat_itrBegin, mat_itrEnd+1);
			}


			RefreshUBOCount(UBO_GLMATERIALS, m_glSceneData->glMaterialList.size());
			break;
		}


		case MOBJECT_TYPE::ZONE:
		{
			shrd_Zone zone = std::static_pointer_cast<Zone>(object);
			for (int i = 0; i < zone->getTerrainList().size(); i++) {
				switch (zone->getTerrainList()[i]->m_terrainType) {
				case TT_GRID: {
					std::vector<shrd_GLTerrain>::iterator itr = std::find_if(m_glSceneData->glTerrainList.begin(), m_glSceneData->glTerrainList.end(), CompareGLTerrain(zone->m_id));


					if (itr != m_glSceneData->glTerrainList.end())
					{

						m_glSceneData->glTerrainList.erase(itr);
					}
					break;
				}
				case TT_TRIMESH:
				{
					
						std::vector<shrd_GLTriangleMesh>::iterator itr = std::find_if(m_glSceneData->glTriMeshList.begin(), m_glSceneData->glTriMeshList.end(), CompareGLTrianlgeMesh(zone->m_id));
						
						if (itr != m_glSceneData->glTriMeshList.end())
						{
							m_glSceneData->glTriMeshList.erase(itr);
						}

					
					break;
				}
				default:
					break;
				}

			}
			
			break;
		}


		case MOBJECT_TYPE::POINTLIGHT:
		{
			shrd_PointLight pointLight = std::static_pointer_cast<PointLight>(object);

			std::vector<shrd_GLTriangleMesh>::iterator triMeshListitr = std::find_if(m_glSceneData->glTriMeshList.begin(), m_glSceneData->glTriMeshList.end(), CompareGLTrianlgeMesh(pointLight->m_id));
			if (triMeshListitr != m_glSceneData->glTriMeshList.end())
				m_glSceneData->glTriMeshList.erase(triMeshListitr);

			std::vector<shrd_GLPointLight>::iterator GLPointLightListitr = std::find_if(m_glSceneData->glPointLightList.begin(), m_glSceneData->glPointLightList.end(), CompareGLPointLight(pointLight->m_id));
			if (GLPointLightListitr != m_glSceneData->glPointLightList.end())
				m_glSceneData->glPointLightList.erase(GLPointLightListitr);
			
			//Bind to shader again to keep in sync
			for (int i = 0; i < m_glSceneData->glPointLightList.size(); i++) {
				m_glSceneData->glPointLightList.at(i)->BindToShader(m_shader, i);
			}
			RefreshUBOCount(UBO_GLPOINTLIGHT, m_glSceneData->glPointLightList.size());
		}

		default:
			break;
		}

		return true;
	}

	//To be called on addition or deletion of a Shader UBO Resource
	void GLRenderer::RefreshUBOCount(const UBOType& type, const size_t& count)
	{
		size_t* info = &(m_uboInfoData.numPointLights);
		info[(size_t)type] = count;
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo_InfoUBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(m_uboInfoData), &m_uboInfoData, GL_DYNAMIC_DRAW);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

	}

	void GLRenderer::Draw(const longInt& frameNumber, uchar* renderedData)
	{
		if (!m_cam) {
			Logger::Message(LOG_SEVERITY::LOG_ERROR, "Camera not initialized for OpenGL renderer.");
			return;
		}
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#ifndef GL_USEDEBUGWINDOW
		glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);
#endif // !GL_USEDEBUGWINDOW

		glViewport(0,0,m_width, m_height);
				
		shrd_Camera cam = SceneManager::getCam();
		
		glm::mat4 viewProj = /*m_cam->m_UBOData.viewproj;*/ *cam->Get_viewProj();
		//m_grid->Draw(frameNumber, viewProj);

		// Use our shader
		glUseProgram(m_shader->m_id);
		gl_check_error();

		// Our ModelViewControllerProjection: multiplication of our 4 matrices		
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		//Render models
		for (int i = 0; i < m_glSceneData->glTriMeshList.size(); i++)
		{
			glm::mat4 MVP = viewProj * (*m_glSceneData->glTriMeshList.at(i)->m_modelTransform); // Remember, matrix multiplication is the other way around
			GLuint mvpID = glGetUniformLocation(m_shader->m_id, "MVP");
			glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

			m_glSceneData->glTriMeshList.at(i)->Draw(frameNumber, m_shader);			
		}

		//Render Terrains
		for (int i = 0; i < m_glSceneData->glTerrainList.size(); i++)
		{
			//glm::mat4 MVP = viewProj * (*m_glSceneData->glTerrainList.at(i)->modelTransform); // Remember, matrix multiplication is the other way around
			//GLuint mvpID = glGetUniformLocation(m_shader->m_id, "MVP");
			//glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

			m_glSceneData->glTerrainList.at(i)->Draw(frameNumber, viewProj);
		}

		gl_check_error();		

#ifdef GL_USEPBO
		//****** Copy rendered data using PBO
		static int index = 0;
		int nextIndex = 0;
		// increment current index first then get the next index
		// "index" is used to read pixels from a framebuffer to a PBO
		// "nextIndex" is used to process pixels in the other PBO
		index = (index + 1) % 2;
		nextIndex = (index + 1) % 2;

#ifdef GL_USEDEBUGWINDOW
		glReadBuffer(GL_BACK);
#else
		glReadBuffer(GL_COLOR_ATTACHMENT0);
#endif
		gl_check_error();

		// Copy Pixel data
		glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_renderedPBO[index]);
		gl_check_error();

		glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, 0);
		gl_check_error();

		//Process pixel data
		glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_renderedPBO[nextIndex]);
		gl_check_error();
		//if (m_renderedData) delete m_renderedData;

		uchar* src = (uchar*)glMapBuffer(GL_PIXEL_PACK_BUFFER_ARB, GL_READ_ONLY_ARB);
		if (src) {
			//TODO: Resizing artefact have to do with changing size of render area but not the container...
			memcpy(renderedData, src, m_width * m_height * 3 * sizeof(uchar));
			//FIBITMAP* bitmap = FreeImage_ConvertFromRawBits(renderedData, m_width, m_height, 3 * m_width, 24, FI_RGBA_RED, FI_RGBA_GREEN, FI_RGBA_BLUE, false);
			//FreeImage_Save(FIF_PNG, bitmap, "test.png", 0);
			//FreeImage_Unload(bitmap);			
		}

		if (!glUnmapBufferARB(GL_PIXEL_PACK_BUFFER_ARB)) {
			Logger::Message(LOG_ERROR, "Cannot unmap PBO");
		}
		glBindBuffer(GL_PIXEL_PACK_BUFFER_ARB, 0);
		
#else
		//////****** Copy from Texture directly
#ifdef GL_USEDEBUGWINDOW
		glReadBuffer(GL_BACK);
#else
		glReadBuffer(GL_COLOR_ATTACHMENT0);
#endif
		gl_check_error();
		if (renderedData) {
			glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, renderedData);

			gl_check_error();
		}
#endif
		gl_check_error();
	}

	void GLRenderer::OnShow()
	{
	}

	void GLRenderer::OnResize(int Width, int Height)
	{
		m_width = Width;
		m_height = Height;
		GLRenderer::resetRenderedTexture();
	}


	GLRenderer::~GLRenderer()
	{
		Destroy();
	}

	void GLRenderer::Destroy()
	{
		if (m_initialized) {
			if (VertexArrayID) glDeleteVertexArrays(1, &VertexArrayID);
			if (Framebuffer) glDeleteFramebuffers(1, &Framebuffer);
			if (renderedTexture) glDeleteTextures(1, &renderedTexture);
			if (depthrenderbuffer) glDeleteRenderbuffers(1, &depthrenderbuffer);
			if (m_renderedPBO[0]) glDeleteBuffers(2, m_renderedPBO);
			if (m_ubo_InfoUBO) glDeleteBuffers(1, &m_ubo_InfoUBO);
			gl_check_error();
		}
		m_initialized = false;
	}


	
	bool GLRenderer::resetRenderedTexture()
	{
		if (Framebuffer) glDeleteFramebuffers(1, &Framebuffer);
		glGenFramebuffers(1, &Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, Framebuffer);

		if (renderedTexture) glDeleteTextures(1, &renderedTexture);
		glGenTextures(1, &renderedTexture);
		glBindTexture(GL_TEXTURE_2D, renderedTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		gl_check_error();
		glBindTexture(GL_TEXTURE_2D, 0);
		////// attach the texture to FBO color attachment point
		glFramebufferTexture2D(GL_FRAMEBUFFER,        // 1. fbo target: GL_FRAMEBUFFER 
			GL_COLOR_ATTACHMENT0,  // 2. attachment point
			GL_TEXTURE_2D,         // 3. tex target: GL_TEXTURE_2D
			renderedTexture,             // 4. tex ID
			0);                    // 5. mipmap level: 0(base)

		if (depthrenderbuffer) glDeleteRenderbuffers(1, &depthrenderbuffer);

		// create a renderbuffer object to store depth info
		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
			m_width, m_height);
		//glBindRenderbuffer(GL_RENDERBUFFER, 0);

		// attach the renderbuffer to depth attachment point
		glFramebufferRenderbuffer(GL_FRAMEBUFFER,      // 1. fbo target: GL_FRAMEBUFFER
			GL_DEPTH_ATTACHMENT, // 2. attachment point
			GL_RENDERBUFFER,     // 3. rbo target: GL_RENDERBUFFER
			depthrenderbuffer);              // 4. rbo ID
		gl_check_error();
		//									 // check FBO status

		//resize PBO
		if (m_renderedPBO[0] || m_renderedPBO[1]) glDeleteBuffers(2, m_renderedPBO);
		glGenBuffersARB(2, m_renderedPBO);
		glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_renderedPBO[0]);
		glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, m_width* m_height * 4, 0, GL_STREAM_READ_ARB);
		glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, m_renderedPBO[1]);
		glBufferDataARB(GL_PIXEL_PACK_BUFFER_ARB, m_width* m_height * 4, 0, GL_STREAM_READ_ARB);

		glBindBufferARB(GL_PIXEL_PACK_BUFFER_ARB, 0);
		gl_check_error();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		gl_check_error();
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
			return false;
		else
			return true;

	}
}