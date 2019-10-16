
#include <windows.h>
#include <CommonUtils.h>
#include <CommonUtils_Lib_OpenGL.h>
#include <CameraController.h>
#include <Controller_ArcBall.h>
#include <Camera.h>
#include <Plugin_Renderer_GL.h>
#include <GLRenderer.h>



using namespace mview;
int WIDTH = 640;
int HEIGHT = 480;

int main()
{
	shrd_int width(new int(WIDTH));
	shrd_int height(new int(HEIGHT));
	mview::shrd_Controller_ArcBall g_controller;
	mview::shrd_Camera cam(new mview::Camera());
	cam->Resize(45.0f, WIDTH, HEIGHT, 0.1f, 100.0f);
	//mview::Plugin_Renderer_GL OpenGLRenderer(WIDTH, HEIGHT, cam);
	//OpenGLRenderer.Init();
	shrd_PluginGL renderer(new Plugin_Renderer_GL(width, height));
	renderer->execute();
	renderer->terminate();

	return 0;
}