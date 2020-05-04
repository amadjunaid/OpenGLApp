#include "GLTriangleMesh.h"


namespace mview {
	/*GLTriangleMesh::GLTriangleMesh()
	{
		check_gl_error();
		attributeBuffers = std::vector<VertexAttributeBuffer>(VERTEX_ATTRIBUTES::VA_COUNT, VertexAttributeBuffer(0, 0, -1));
	}*/

	GLTriangleMesh::GLTriangleMesh(shrd_TriangleMesh triMesh, longInt globalId, shrd_mat4 modelTrasform): GLObject(globalId)
	{
		gl_check_error();
		attributeBuffers = std::vector<VertexAttributeBuffer>(VERTEX_ATTRIBUTES::VA_COUNT, VertexAttributeBuffer(0, 0, -1));
		m_triMesh = triMesh;
		m_globalId = globalId;
		for (int i = 0; i < triMesh->m_vertices.size(); i++)
		{
			if (triMesh->m_vertices.at(i).unstructuredData.size() > 0)
			{
				resetData((VERTEX_ATTRIBUTES)i, triMesh->m_vertices.at(i).unstructuredData.data(), (int)triMesh->m_vertices.at(i).unstructuredData.size(), GL_FLOAT);
			}
		}
		m_modelTransform = modelTrasform;

		m_textures = GLTexturesList(std::vector<shrd_GLTexture>(TEXTURE_TYPE::TT_COUNT, 0));
	}


	void GLTriangleMesh::resetData(VERTEX_ATTRIBUTES attributeType, const GLfloat * data, int size, int type)
	{
		if (attributeBuffers.at(attributeType).m_id)
			glDeleteBuffers(1, &(attributeBuffers.at(attributeType).m_id));
		glGenBuffers(1, &(attributeBuffers.at(attributeType).m_id));
		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers.at(attributeType).m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*size, data, GL_STATIC_DRAW);
		
		gl_check_error();
		attributeBuffers.at(attributeType).m_type = type;
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void GLTriangleMesh::UpdateParam(int name)
	{
	}

	void GLTriangleMesh::Draw(const longInt& frameNumber, const shrd_GLShaderTechnique shader)
	{
		

		//Bind shader uniforms
		GLuint ModelMatrixID = glGetUniformLocation(shader->m_id, "M");		
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &(*m_modelTransform)[0][0]);

		GLuint materialID = glGetUniformLocation(shader->m_id, "materialID");
		glUniform1i(materialID, (GLint)m_materialndex);	


		//Configure attribute buffers
		for (int i = 0; i < attributeBuffers.size(); i++) {
			if (attributeBuffers.at(i).m_id) {
				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(i);
				gl_check_error();
				glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers.at(i).m_id);
				gl_check_error();
				glVertexAttribPointer(
					i,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					VertexAttribute::ElementsPerVertex(i),                  // size per element e.g. 3 for a 3 vector
					attributeBuffers.at(i).m_type,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);
				gl_check_error();
			}
		}

		//Setup textures for the mesh
		for (int j = 0; j < TEXTURE_TYPE::TT_COUNT; j++) {
			if (m_textures[j] && m_textures[j]->m_GLId) {
				glActiveTexture(GL_TEXTURE0 + j);
				GLuint TextureID = glGetUniformLocation(shader->m_id, GLTexture::GetTexNameinShader(TEXTURE_TYPE(j)).c_str());

				//Bind our texture in Texture Unit 0					
				glBindTexture(GL_TEXTURE_2D, m_textures[j]->m_GLId);

				// Set our "myTextureSampler" sampler to user Texture Unit 0
				glUniform1i(TextureID, j);
				gl_check_error();
			}
		}

		switch (m_renderMode->Get()) {
		case RM_WIREFRAME:
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			gl_check_error();
			break;
		case RM_NORMAL:
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			gl_check_error();
			break;
		default:
			break;
		}

		glDrawArrays(GL_TRIANGLES, 0, (int)m_triMesh->m_numTris * 3); // 3 indices starting at 0 -> 1 triangle		


		for (int j = 0; j < TEXTURE_TYPE::TT_COUNT; j++)
		{
			glActiveTexture(GL_TEXTURE0 + j);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		gl_check_error();

	}


	GLTriangleMesh::~GLTriangleMesh()
	{
		for (int i = 0; i < attributeBuffers.size(); i++)
		{
			if (attributeBuffers.at(i).m_id) glDeleteBuffers(1, &(attributeBuffers.at(i).m_id));
		}
#ifdef _DEBUG
		Logger::Message(LOG_INFO, "Renderer data (Triangle data for " + m_triMesh->m_objectName +") deleted.");
#endif
	}	
	
}