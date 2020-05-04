
#ifndef PLUGIN_RENDERER_GL_H
#define PLUGIN_RENDERER_GL_H


#include <Model.h>
#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>

#include "CommonUtils_Lib_OpenGL.h"

#include "GLGrid.h"
#include "GLShader.h"
#include "GLTexture.h"
#include "GLTriangleMesh.h"
#include "GLMaterial.h"
#include "GLCamera.h"
#include "GLPointLight.h"
#include "Plugin_Renderer.h"
#include "GLTerrain.h"


namespace mview {

	//************
	//Provides GL rendering functionality
	//************

	struct GLSceneData {		
		GLTriangleMeshList glTriMeshList;
		GLTerrainList glTerrainList;
		GLPointLightList glPointLightList;
		GLMaterialList glMaterialList;		
	};

	typedef std::shared_ptr<GLSceneData> shrd_GLSceneData;

	class GLRenderer 
	{
	private:
		GLuint m_renderedPBO[2];
		GLuint Framebuffer;
		GLuint renderedTexture;
		GLuint depthrenderbuffer;
		GLuint m_ubo_InfoUBO = 0;
		UBOInfoData m_uboInfoData;
		GLuint VertexArrayID;
		

	protected:
		int m_width, m_height;
				

		shrd_GLShaderTechnique m_shader;		

		shrd_GLSceneData m_glSceneData;
		shrd_GLCamera m_cam;
		
		bool resetRenderedTexture();	

	public:
		bool m_initialized = false;
		GLRenderer();
		GLRenderer(int width, int height);
		bool Init();		
		bool AddSceneData(const shrd_MObject object);
		bool ReplaceSceneData(const shrd_MObject object);
		void ChangeSceneDataParam(const shrd_MObject object, int param);
		bool RemoveSceneData(const shrd_MObject object);
		void RefreshUBOCount(const UBOType& type, const size_t& count);

		void Draw(const longInt& frameNumber, uchar* renderedData);		
		void OnShow();
		void OnResize(int Width, int Height);
		~GLRenderer();
		void Destroy();
	};

	typedef std::shared_ptr<GLRenderer> shrd_GLRenderer;
}


#endif // !PLUGIN_RENDERER_GL_H