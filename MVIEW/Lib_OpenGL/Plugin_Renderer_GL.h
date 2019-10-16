
#ifndef GLINITIALIZER_H
#define GLINITIALIZER_H

#include "CommonUtils_Lib_OpenGL.h"

#include <GLFW\glfw3.h>
#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>

#include <glm/glm.hpp>

#include <Camera.h>
#include <memory>
#include "GLRenderer.h"
#include "GLTriangleMesh.h"
#include "GLPointLight.h"
#include <Threadable.h>
#include <Plugin_Renderer.h>
#include <SceneObject.h>

namespace mview {
	class DLLEXPORT Plugin_Renderer_GL: public Plugin_Renderer
	{
	private:
		GLFWwindow* GLWnd;
		int m_glVersion;

		shrd_GLRenderer m_renderer;

		double xpos = 0; 
		double ypos = 0;
	protected:
		void executable();
		
	public:
		Plugin_Renderer_GL();
		Plugin_Renderer_GL(shrd_int width, shrd_int height);
		bool Init();
		
		void MoveMouse();
		
		void OnPaint();
		void OnShow();
		void OnResize();
		void OnDataRefresh();
		~Plugin_Renderer_GL();		
		void Destroy();	

	};

	typedef std::shared_ptr<mview::Plugin_Renderer_GL> shrd_PluginGL;	
}


#endif /*PLUGIN_H*/