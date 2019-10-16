#include "Plugin_Renderer_GL.h"
#include "GLRenderer.h"
#include <iostream>



namespace mview {

	Plugin_Renderer_GL::Plugin_Renderer_GL() : Plugin_Renderer()
	{

	}

	Plugin_Renderer_GL::Plugin_Renderer_GL(shrd_int width, shrd_int height) :
		Plugin_Renderer(width, height)
	{
		if (!g_width || !g_height)
		{
			Logger::Message(LOG_ERROR, "Height and Width must be initialized before Renderer initialization." );
			return;
		}
		m_renderer.reset( new GLRenderer(*g_width, *g_height));				
	}

	bool Plugin_Renderer_GL::Init()
	{
		//////////////////////////////////////// Window Initialization : GLFW /////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Initialise GLFW
		if (!glfwInit())
		{
			Logger::Message(LOG_ERROR, "Failed to initialize GLFW");
			getchar();
			return false;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);

		if (!g_width || !g_height)
		{
			return false;
		}
		// Open a window and create its OpenGL context
		GLWnd = glfwCreateWindow(*g_width, *g_height, "Tutorial 0 - Keyboard and Mouse", NULL, NULL);
		if (GLWnd == NULL) {
			Logger::Message(LOG_ERROR, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.");
			getchar();
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(GLWnd);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			Logger::Message(LOG_ERROR, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			return false;
		}
		int major, minor;

		sscanf_s((char*)glGetString(GL_VERSION), "%d.%d", &major, &minor);
		Logger::Message(LOG_INFO, "GL Version: " + std::to_string(major) + "." + std::to_string(minor));

		int UBOAllowedInVert;
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_BLOCKS, &UBOAllowedInVert);
		int UBOAllowedInGeo;
		glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &UBOAllowedInGeo);
		int UBOAllowedInFrg;
		glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &UBOAllowedInFrg);

		Logger::Message(LOG_INFO, "UBOs allowed for Vertex Shaders: " + std::to_string(UBOAllowedInVert));
		Logger::Message(LOG_INFO, "UBOs allowed for Geometry Shaders: " + std::to_string(UBOAllowedInGeo));
		Logger::Message(LOG_INFO, "UBOs allowed for Fragment Shaders: " + std::to_string(UBOAllowedInFrg));
		
		

		m_glVersion = major * 10 + minor;
		suppress_gl_error();
		// Ensure we can capture the escape key being pressed below
		//glfwSetInputMode(GLWnd, GLFW_STICKY_KEYS, GL_TRUE);

		//// Hide the mouse and enable unlimited mouvement
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Set the mouse at the center of the screen
		glfwPollEvents();
		//glfwSetInputMode(GLWnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		//glfwSetCursorPosCallback(GLWnd, cursor_position_callback);

#ifndef GL_USEDEBUGWINDOW
		glfwHideWindow(GLWnd);
#endif //
		//m_renderedData = new uchar[m_width * m_height * 3]();
		if (!m_renderer->Init()) {			
			std::cout << "Could not initialize GL stuff properly." << std::endl;
			return false;
		}
		
		//glfwSwapInterval(1); //(0 = off, 1 = on)
		return m_initialized = true;
	}

	

	void Plugin_Renderer_GL::MoveMouse()
	{
		//glfwGetCursorPos(GLWnd, &xpos, &ypos);
		//if( xpos >=0 && xpos<= *g_width && ypos >= 0 && ypos <= *g_height)
		////std::cout << "Mouse Coordinates:" << xpos << ", " << ypos << std::endl;
		//if ( glfwGetMouseButton(GLWnd, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//	g_cam->Get_controller()->MouseClick((mview::BUTTON::LEFT), xpos, ypos);
		//}
		//else if (glfwGetMouseButton(GLWnd, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		//	g_cam->Get_controller()->MouseClick((mview::BUTTON::RIGHT), xpos, ypos);
		//}
		//else if (glfwGetMouseButton(GLWnd, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		//	g_cam->Get_controller()->MouseClick((mview::BUTTON::MIDDLE), xpos, ypos);
		//}
		//else {
		//	g_cam->Get_controller()->MouseRelease(xpos, ypos);
		//}

	}

	

	void Plugin_Renderer_GL::OnPaint()
	{
		
		m_renderer->Draw(m_frameNumber, m_threadedRenderedData[RenderBuffers::BACK].m_dataPtr);
			
		//Swapping buffers for the local rendered data
		m_threadedRenderedData[RenderBuffers::FRONT].AtomicClose();
		auto tempRenderData = m_threadedRenderedData[RenderBuffers::BACK].m_dataPtr;
		m_threadedRenderedData[RenderBuffers::BACK].m_dataPtr = m_threadedRenderedData[RenderBuffers::FRONT].m_dataPtr;
		m_threadedRenderedData[RenderBuffers::FRONT].m_dataPtr = tempRenderData;
		m_threadedRenderedData[RenderBuffers::FRONT].AtomicOpen();
	}

	void Plugin_Renderer_GL::OnShow()
	{		
	}

	void Plugin_Renderer_GL::OnResize()
	{
		//atomicClose();
		m_threadedRenderedData[RenderBuffers::FRONT].AtomicClose();
		m_threadedRenderedData[RenderBuffers::BACK].AtomicClose();
		glfwSetWindowSize(GLWnd, *g_width, *g_height);
		if (m_threadedRenderedData[RenderBuffers::FRONT].m_dataPtr) {
			delete m_threadedRenderedData[RenderBuffers::FRONT].m_dataPtr;
			delete m_threadedRenderedData[RenderBuffers::BACK].m_dataPtr;
		}
		m_threadedRenderedData[RenderBuffers::FRONT].m_dataPtr = new uchar[*g_width * *g_height * 4]();
		m_threadedRenderedData[RenderBuffers::BACK].m_dataPtr = new uchar[*g_width * *g_height * 4]();
		

		m_renderer->OnResize(*g_width, *g_height);		
		m_threadedRenderedData[RenderBuffers::FRONT].AtomicOpen();
		m_threadedRenderedData[RenderBuffers::BACK].AtomicOpen();
		//atomicOpen();
	}

	void Plugin_Renderer_GL::OnDataRefresh()
	{
		moodycamel::ConcurrentQueue<shrd_DataRefresh>& dataRefreshList = GetDataRefresh();
		shrd_DataRefresh dataRefresh;
		//Logger::Message(LOG_INFO, "Entered DataConsumption");
		while (dataRefreshList.try_dequeue(dataRefresh)) {
			
			switch (dataRefresh->action) {
			case DATA_ACTION::ADD:
				m_renderer->AddSceneData(dataRefresh->obj);
				break;
			case DATA_ACTION::REMOVE:
				m_renderer->RemoveSceneData(dataRefresh->obj);
				break;
			case DATA_ACTION::REPLACE:
				m_renderer->ReplaceSceneData(dataRefresh->obj);
				break;
			case DATA_ACTION::CHANGEPARAM:
				m_renderer->ChangeSceneDataParam(dataRefresh->obj, dataRefresh->modifiedParam);
				break;
			default:
				break;
			}
			//dataRefreshList.try_dequeue();
			
		}
		//Logger::Message(LOG_INFO, "Left DataConsumption");
	}

	void Plugin_Renderer_GL::Destroy()
	{
		m_initialized = false;
	}

	Plugin_Renderer_GL::~Plugin_Renderer_GL()
	{
		Destroy();				
	}

	
	void Plugin_Renderer_GL::executable()
	{
		if (Init() && !isTerminated)
		{
			//while (!m_startRendering);
			OnResize();
			m_startTime = GetTickCount();
			
			do {
				static double frameTimeAggregate = 0.0;
				DWORD End = GetTickCount();
				
#ifdef GL_USEDEBUGWINDOW
				MoveMouse();
#endif // GL_USEDEBUGWINDOW
				OnPaint();
				double FrameTime = (End - m_startTime) * 0.001f;
				m_startTime = End;
				ThreadSleep(5);
				m_frameNumber++;

#ifdef GL_SHOWFRAMETIME
				///////////////////////////////////////
				frameTimeAggregate += FrameTime;
				if (m_frameNumber % 60 == 0) {
					double time1Frame = frameTimeAggregate / 60.0;
					Logger::Message(LOG_SEVERITY::LOG_INFO, "Frame being rendered in: " + std::to_string(time1Frame) + " milli secs");
					frameTimeAggregate = 0.0;
				}
				///////////////////////////////////////
#endif
				// Swap buffers
#ifdef GL_USEDEBUGWINDOW
				glfwSwapBuffers(GLWnd);
#endif
				glfwPollEvents();
				ProcessEvents();		

			} while (!isTerminated && glfwGetKey(GLWnd, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
				glfwWindowShouldClose(GLWnd) == 0);
			// Close OpenGL window and terminate GLFW
			m_renderer = nullptr;
			glfwTerminate();
		}
		else
		{
			Logger::Message(LOG_ERROR, "Cannot create Window.");
		}
	}

}