
#ifndef PLUGIN_H
#define PLUGIN_H

#include "CommonUtils_Lib_OpenGL.h"
#include "GLRenderer.h"

#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>

#include <glm/glm.hpp>

#include <Threadable.h>
#include <Plugin_Renderer.h>
#include <memory>


namespace mview {
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	
	//************
	//Implementation of an OpenGL renderer. Uses Plugin_Renderer as base.
	//************	
	class DllExport PluginGL : public Plugin_Renderer
	{
	private:
		GLRenderer m_GLRenderer;		

	protected:
		int m_widthD2, m_heightD2;
		

		int m_samples;
		int m_glVersion;
		bool m_wglContextForwardCompatible;
		int m_glMaxTextureSize;
		int m_glMaxTextureMaxAnisotropyExt;
		HGLRC m_hGLRC;
		
		HDC m_hDC;
		DWORD m_start, m_begin;
		HINSTANCE m_hinstance;
		
		std::mutex m_resizeMtx;
		void StartFPSCounter();

	public:
		
		HWND m_hWnd;

		PluginGL();
		PluginGL(int width, int height);
		~PluginGL();

		bool Create(char *Name);

		void OnShow();
		void Destroy();

		void OnPaint( );

		void OnMouseMove(int cx, int cy);

		void OnResize(int sx, int sy);

		void MsgLoop();

		void run( );
		
	};

	typedef std::shared_ptr<mview::PluginGL> shrd_PluginGL;
}


#endif /*PLUGIN_H*/