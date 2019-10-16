#pragma once
#include <CommonUtils.h>
#include <CommonUtils_Lib_OpenGL.h>
#include <Plugin_Renderer_GL.h>
#include <Camera.h>

#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>

#include <glm/glm.hpp>

using namespace mview;
using namespace glm;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class CWnd
{
private:
	shrd_Plugin_Renderer_GL OpenGLRenderer;

	// The actual windows procedure that gets called after
	//   the WM_NCCREATE message is processed. This is a member
	//   function so you can access member variables and such here.
	//   Or just call other member functions to handle the messages
	LRESULT CALLBACK ActualWndProc(UINT Msg, WPARAM wParam, LPARAM lParam);

	// The first windows procedure used by the window class.
	//   It's only purpose is to wait till WM_NCCREATE is sent and
	//   then jam the MyWindowClass pointer into the user data
	//   portion of the window instance. Then, having done its duty
	//   it changes the windows procedure to StaticWndProc()
	static LRESULT CALLBACK InitialWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

	// This function's sole purpose in life is to take the pointer from
	//   the user data portion of the window instance and call the actual
	//   windows procedure on that pointer. It does no special handling for
	//   any messages.
	static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

protected:
	char *WindowName;
	bool FullScreen, DeFullScreened;
	DEVMODE DevMode;
	HWND m_hWnd;
	HDC hDC;
	int Samples;
	HGLRC hGLRC;
	int Width, Height, WidthD2, HeightD2;
	DWORD Start, Begin;
	POINT LastCurPos;
	bool MouseGameMode, KeyBoardFocus, MouseFocus;
	int m_glVersion;
	bool m_wglContextForwardCompatible;
	int m_glMaxTextureSize;
	int m_glMaxTextureMaxAnisotropyExt;
	shrd_Camera m_cam;

public:
	CWnd();
	~CWnd();

	bool Create(HINSTANCE hInstance, char *WindowName, int Width, int Height, bool FullScreen = false, int Samples = 4, bool CreateForwardCompatibleContext = false, bool DisableVerticalSynchronization = true);
	void Show(bool MouseGameMode = false, bool Maximized = false);
	void MsgLoop();
	void Destroy();

protected:
	void GetCurPos(int *cx, int *cy);
	void SetCurPos(int cx, int cy);
	void SetCurAccToMouseGameMode();
	void SetMouseFocus();
	void StartFPSCounter();

public:
	void OnKeyDown(UINT nChar);
	void OnKillFocus();
	void OnLButtonDown(int cx, int cy);
	void OnMouseMove(int cx, int cy);
	void OnMouseWheel(short zDelta);
	void OnPaint();
	void OnRButtonDown(int cx, int cy);
	void OnSetFocus();
	void OnSize(int sx, int sy);
};


