#include "Cwnd.h"
#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>


CWnd::CWnd()
{
	DeFullScreened = false;
}

CWnd::~CWnd()
{
}


bool CWnd::Create(HINSTANCE hInstance, char *WindowName, int Width, int Height, bool FullScreen, int Samples, bool CreateForwardCompatibleContext, bool DisableVerticalSynchronization)
{
	WNDCLASSEXA WndClassEx;

	memset(&WndClassEx, 0, sizeof(WNDCLASSEXA));
	
	WndClassEx.cbSize = sizeof(WNDCLASSEXA);
	WndClassEx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WndClassEx.lpfnWndProc = &CWnd::InitialWndProc;
	WndClassEx.hInstance = hInstance;
	WndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClassEx.lpszClassName = "Win32OpenGLWindowClass";

	if (!RegisterClassExA(&WndClassEx))
	{
		std::cout<< "RegisterClassEx failed!" <<std::endl;
		return false;
	}

	this->WindowName = WindowName;

	this->Width = Width;
	this->Height = Height;

	DWORD Style = (FullScreen ? WS_POPUP : WS_OVERLAPPEDWINDOW) | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if ((m_hWnd = CreateWindowExA(WS_EX_APPWINDOW, WndClassEx.lpszClassName, WindowName, Style, 0, 0, Width, Height, NULL, NULL, hInstance, this)) == NULL)
	{
		std::cout<< "CreateWindowEx failed!"<< std::endl;		
		return false;
	}

	this->FullScreen = FullScreen;

	if (FullScreen)
	{
		memset(&DevMode, 0, sizeof(DEVMODE));

		DevMode.dmSize = sizeof(DEVMODE);
		DevMode.dmPelsWidth = Width;
		DevMode.dmPelsHeight = Height;
		DevMode.dmBitsPerPel = 32;
		DevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		this->FullScreen = ChangeDisplaySettings(&DevMode, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL;
	}

	if ((hDC = GetDC(m_hWnd)) == NULL)
	{
		std::cout<<"GetDC failed!"<<std::endl;
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;

	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int PixelFormat;

	if ((PixelFormat = ChoosePixelFormat(hDC, &pfd)) == 0)
	{
		std::cout<< "ChoosePixelFormat failed!\0" << std::endl;
		return false;
	}

	static int MSAAPixelFormat = 0;

	if (SetPixelFormat(hDC, MSAAPixelFormat == 0 ? PixelFormat : MSAAPixelFormat, &pfd) == FALSE)
	{

		std::cout << "SetPixelFormat failed!\0" << std::endl;
		return false;
	}

	if ((hGLRC = wglCreateContext(hDC)) == NULL)
	{
		std::cout << "wglCreateContext failed!\0" << std::endl;
		return false;
	}

	if (wglMakeCurrent(hDC, hGLRC) == FALSE)
	{
		std::cout << "wglMakeCurrent failed!\0" << std::endl;
		return false;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glewInit failed!\0" << std::endl;
		return false;
	}

	/*if (MSAAPixelFormat == 0 && Samples > 0)
	{
		if (GLEW_ARB_multisample && WGLEW_ARB_pixel_format)
		{
			while (Samples > 0)
			{
				UINT NumFormats = 0;

				int iAttributes[] =
				{
					WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
					WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
					WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
					WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
					WGL_COLOR_BITS_ARB, 32,
					WGL_DEPTH_BITS_ARB, 24,
					WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
					WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
					WGL_SAMPLES_ARB, Samples,
					0
				};

				if (wglChoosePixelFormatARB(hDC, iAttributes, NULL, 1, &MSAAPixelFormat, &NumFormats) == TRUE && NumFormats > 0) break;

				Samples--;
			}

			wglDeleteContext(hGLRC);

			DestroyWindow(m_hWnd);

			UnregisterClassA(WndClassEx.lpszClassName, hInstance);

			return Create(hInstance, WindowName, Width, Height, FullScreen, Samples, CreateForwardCompatibleContext, DisableVerticalSynchronization);
		}
		else
		{
			Samples = 0;
		}
	}*/

	this->Samples = Samples;

	int major, minor;

	sscanf_s((char*)glGetString(GL_VERSION), "%d.%d", &major, &minor);
	std::cout << "GL Ver: " << major << "." << minor << std::endl;

	m_glVersion = major * 10 + minor;

	if (CreateForwardCompatibleContext && m_glVersion >= 30 && WGLEW_ARB_create_context)
	{
		wglDeleteContext(hGLRC);

		int GLFCRCAttribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, major,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0
		};

		if ((hGLRC = wglCreateContextAttribsARB(hDC, 0, GLFCRCAttribs)) == NULL)
		{

			std::cout << "wglCreateContextAttribsARB failed!\0"<<std::endl;
			return false;
		}

		if (wglMakeCurrent(hDC, hGLRC) == FALSE)
		{
			std::cout << "wglMakeCurrent failed!\0" << std::endl;
			return false;
		}

		m_wglContextForwardCompatible = true ;
	}
	else
	{
		m_wglContextForwardCompatible = false ;
	}

	
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_glMaxTextureSize);

	if (GLEW_EXT_texture_filter_anisotropic)
	{
		glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_glMaxTextureMaxAnisotropyExt);		
	}

	if (DisableVerticalSynchronization  && WGLEW_EXT_swap_control)
	{
		wglSwapIntervalEXT(0);
	}

	m_cam.reset(new mview::Camera(nullptr));
	OpenGLRenderer.reset(new mview::Pulgin_Renderer_GL(this->Width, this->Height, m_cam));
	return OpenGLRenderer->Init();
}

void CWnd::Show(bool MouseGameMode, bool Maximized)
{
	this->MouseGameMode = MouseGameMode;

	if (!FullScreen)
	{
		RECT dRect, wRect, cRect;

		GetWindowRect(GetDesktopWindow(), &dRect);
		GetWindowRect(m_hWnd, &wRect);
		GetClientRect(m_hWnd, &cRect);

		wRect.right += Width - cRect.right;
		wRect.bottom += Height - cRect.bottom;

		wRect.right -= wRect.left;
		wRect.bottom -= wRect.top;

		wRect.left = dRect.right / 2 - wRect.right / 2;
		wRect.top = dRect.bottom / 2 - wRect.bottom / 2;

		MoveWindow(m_hWnd, wRect.left, wRect.top, wRect.right, wRect.bottom, FALSE);
	}
	else
	{
		this->MouseGameMode = true;
	}
	m_cam->Resize(45.0, this->Width, this->Height, 0.1f, 100.f);
	OpenGLRenderer->OnResize(Width, Height);

	StartFPSCounter();

	ShowWindow(m_hWnd, (!FullScreen && Maximized) ? SW_SHOWMAXIMIZED : SW_SHOWNORMAL);

	SetForegroundWindow(m_hWnd);

	KeyBoardFocus = MouseFocus = true;

	SetCurAccToMouseGameMode();
}

void CWnd::MsgLoop()
{
	MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void CWnd::Destroy()
{
	wglDeleteContext(hGLRC);

	DestroyWindow(m_hWnd);	
}

void CWnd::GetCurPos(int *cx, int *cy)
{
	POINT Point;

	GetCursorPos(&Point);

	ScreenToClient(m_hWnd, &Point);

	*cx = Point.x;
	*cy = Point.y;
}

void CWnd::SetCurPos(int cx, int cy)
{
	POINT Point;

	Point.x = cx;
	Point.y = cy;

	ClientToScreen(m_hWnd, &Point);

	SetCursorPos(Point.x, Point.y);
}

void CWnd::SetCurAccToMouseGameMode()
{
	if (MouseGameMode)
	{
		SetCurPos(WidthD2, HeightD2);
		while (ShowCursor(FALSE) >= 0);
	}
	else
	{
		while (ShowCursor(TRUE) < 0);
	}
}

void CWnd::SetMouseFocus()
{
	SetCurAccToMouseGameMode();
	MouseFocus = true;
}

void CWnd::StartFPSCounter()
{
	Start = Begin = GetTickCount();
}

void CWnd::OnKeyDown(UINT nChar)
{
	switch (nChar)
	{
	case VK_ESCAPE:
		PostQuitMessage(0);
		break;

	case VK_F1:
		//OpenGLRenderer.ShowAxisGrid = !OpenGLRenderer.ShowAxisGrid;
		break;

	case VK_F2:
		if (!FullScreen && MouseFocus)
		{
			MouseGameMode = !MouseGameMode;
			SetCurAccToMouseGameMode();
		}
		break;

	case VK_F3:
		if (!FullScreen)
		{
			WINDOWPLACEMENT WndPlcm;
			WndPlcm.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(m_hWnd, &WndPlcm);
			if (WndPlcm.showCmd == SW_SHOWNORMAL) ShowWindow(m_hWnd, SW_SHOWMAXIMIZED);
			if (WndPlcm.showCmd == SW_SHOWMAXIMIZED) ShowWindow(m_hWnd, SW_SHOWNORMAL);
		}
		break;

	case VK_SPACE:
		//OpenGLRenderer.Stop = !OpenGLRenderer.Stop;
		break;
	}
}

void CWnd::OnKillFocus()
{
	if (MouseFocus && MouseGameMode)
	{
		while (ShowCursor(TRUE) < 0);
	}

	KeyBoardFocus = MouseFocus = false;

	if (FullScreen)
	{
		ShowWindow(m_hWnd, SW_SHOWMINIMIZED);
		ChangeDisplaySettings(NULL, 0);
		DeFullScreened = true;
	}
}

void CWnd::OnLButtonDown(int cx, int cy)
{
	SetMouseFocus();
}

void CWnd::OnMouseMove(int cx, int cy)
{
	if (MouseGameMode && MouseFocus)
	{
		if (cx != WidthD2 || cy != HeightD2)
		{
			//OpenGLRenderer.getCamera()->OnMouseMove(WidthD2 - cx, HeightD2 - cy);
			SetCurPos(WidthD2, HeightD2);
		}
	}
	else if (GetKeyState(VK_RBUTTON) & 0x80)
	{
		//OpenGLRenderer.getCamera()->OnMouseMove(LastCurPos.x - cx, LastCurPos.y - cy);

		LastCurPos.x = cx;
		LastCurPos.y = cy;
	}
}

void CWnd::OnMouseWheel(short zDelta)
{
	//OpenGLRenderer.getCamera()->OnMouseWheel(zDelta);
}

void CWnd::OnPaint()
{
	PAINTSTRUCT ps;

	BeginPaint(m_hWnd, &ps);

	static int FPS = 0;

	DWORD End = GetTickCount();

	float FrameTime = (End - Begin) * 0.001f;
	Begin = End;

	if (End - Start > 1000)
	{
		std::string Text = WindowName;

		Text += " - %dx%d" + Width + Height;
		Text += ", ATF %dx" + m_glMaxTextureMaxAnisotropyExt;
		Text += ", MSAA %dx" + Samples;
		Text += ", FPS: %d" + FPS;
		/*Text.Append(" - OpenGL %d.%d", gl_version / 10, gl_version % 10);
		if(get_gl_version() >= 30) if(get_wgl_context_forward_compatible()) Text.Append(" Forward compatible"); else Text.Append(" Compatibility profile");*/
		Text += " - %s" + std::string((char*)glGetString(GL_RENDERER));

		SetWindowTextA(m_hWnd, Text.c_str());

		FPS = 0;
		Start = End;
	}
	else
	{
		FPS++;
	}

	if (KeyBoardFocus)
	{
		BYTE Keys = 0x00;

		if (GetKeyState('W') & 0x80) Keys |= 0x01;
		if (GetKeyState('S') & 0x80) Keys |= 0x02;
		if (GetKeyState('A') & 0x80) Keys |= 0x04;
		if (GetKeyState('D') & 0x80) Keys |= 0x08;
		if (GetKeyState('R') & 0x80) Keys |= 0x10;
		if (GetKeyState('F') & 0x80) Keys |= 0x20;

		if (GetKeyState(VK_SHIFT) & 0x80) Keys |= 0x40;

		if (Keys & 0x3F)
		{
			//vec3 Movement = OpenGLRenderer.getCamera()->OnKeys(Keys, FrameTime);
			//OpenGLRenderer.getCamera()->Move(Movement);
		}
	}

	OpenGLRenderer->OnPaint();

	SwapBuffers(hDC);

	EndPaint(m_hWnd, &ps);

	InvalidateRect(m_hWnd, NULL, FALSE);
}

void CWnd::OnRButtonDown(int cx, int cy)
{
	SetMouseFocus();

	if (!MouseGameMode)
	{
		LastCurPos.x = cx;
		LastCurPos.y = cy;
	}
}

void CWnd::OnSetFocus()
{
	KeyBoardFocus = true;

	if (DeFullScreened)
	{
		ChangeDisplaySettings(&DevMode, CDS_FULLSCREEN);
		MoveWindow(m_hWnd, 0, 0, DevMode.dmPelsWidth, DevMode.dmPelsHeight, FALSE);
		DeFullScreened = false;
	}

	int cx, cy;

	GetCurPos(&cx, &cy);

	if (cx >= 0 && cx < Width && cy >= 0 && cy < Height)
	{
		SetMouseFocus();
	}
}

void CWnd::OnSize(int sx, int sy)
{
	if (Width == 0 && Height == 0)
	{
		StartFPSCounter();
	}

	Width = sx;
	Height = sy;

	WidthD2 = Width / 2;
	HeightD2 = Height / 2;

	m_cam->Resize(45.0, this->Width, this->Height, 0.1f, 100.f);
	OpenGLRenderer->OnResize(Width, Height);	
}

LRESULT CALLBACK CWnd::ActualWndProc(UINT Msg, WPARAM wParam, LPARAM lParam) {
	switch (Msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CREATE:
	{
		// all this does is perform a sanity check as it should be
		//   called after WM_NCCREATE
		LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		void * lpCreateParam = create_struct->lpCreateParams;
		CWnd * this_window = reinterpret_cast<CWnd *>(lpCreateParam);
		assert(this_window == this);
		return DefWindowProc(m_hWnd, Msg, wParam, lParam);
	}

	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		OnKeyDown((UINT)wParam);
		break;

	case WM_KILLFOCUS:
		OnKillFocus();
		break;

	case WM_LBUTTONDOWN:
		OnLButtonDown(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_MOUSEMOVE:
		OnMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;

	case 0x020A: // WM_MOUSWHEEL
		OnMouseWheel(HIWORD(wParam));
		break;

	case WM_PAINT:
		OnPaint();
		break;

	case WM_RBUTTONDOWN:
		OnRButtonDown(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_SETFOCUS:
		OnSetFocus();
		break;

	case WM_SIZE:
		OnSize(LOWORD(lParam), HIWORD(lParam));
		break;

	default:
		return DefWindowProc(m_hWnd, Msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK CWnd::InitialWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	if (Msg == WM_NCCREATE) {
		LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		void * lpCreateParam = create_struct->lpCreateParams;
		CWnd * this_window = reinterpret_cast<CWnd *>(lpCreateParam);
		//assert(this_window->m_hWnd == 0); // this should be the first (and only) time
										  // WM_NCCREATE is processed
		this_window->m_hWnd = hWnd;
		SetWindowLongPtr(hWnd,
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(this_window));
		SetWindowLongPtr(hWnd,
			GWLP_WNDPROC,
			reinterpret_cast<LONG_PTR>(&CWnd::StaticWndProc));
		return this_window->ActualWndProc(Msg, wParam, lParam);
	}
	// if it isn't WM_NCCREATE, do something sensible and wait until
	//   WM_NCCREATE is sent                                   
	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

LRESULT CALLBACK CWnd::StaticWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
	LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	CWnd * this_window = reinterpret_cast<CWnd *>(user_data);
	assert(this_window); // WM_NCCREATE should have assigned the pointer
	assert(hWnd == this_window->m_hWnd);
	return this_window->ActualWndProc(Msg, wParam, lParam);
}

