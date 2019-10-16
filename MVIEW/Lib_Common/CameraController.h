
#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "CommonUtils.h"
#include "Param.h"



namespace mview {
	//Forward declaration
	class Camera;
	struct Viewport;
	typedef std::shared_ptr<Camera> shrd_Camera;
	enum DLLEXPORT CONTROLLERS {CONTROLLER_ARCBALL, CONTROLLER_WALKER, CONTROLLER_COUNT};
	enum DLLEXPORT BUTTON{LEFT, RIGHT, MIDDLE};
	enum DLLEXPORT KEY {A, S, D, W, Q, E, C, Y};
	//************
	//Base class to use controllers for mouse and keyboard inputs
	//************
	class DLLEXPORT CameraController
	{

	protected:	
		glm::mat4 m_rotationMat = glm::mat4(1.f);	//Rotation matrix to be applied to the view
		glm::vec3 m_translationVec = glm::vec3(0.f);		
		
		//glm::vec2 m_translation = glm::vec2(0.f, 0.f); //Translation matrix

		shrd_mat4 m_viewMat_cam;
		shrd_Param_mat4 m_combinedViewMat;
	public:
		CameraController(shrd_mat4 m_viewMat_cam, shrd_Param_mat4 m_viewMat_combined);
		virtual ~CameraController();
		
		virtual void Reset(); //For parameter reset
		virtual void Resize(const int& width, const int& height, const glm::vec3& eye, const glm::vec3& up, const glm::mat4& viewMat, const glm::mat4& projMat, const Viewport& viewport);  //In case controller needs to do something during resize

		//Control functions
		virtual void MouseClick(const BUTTON& btn, const int& cx, const int& cy);
		virtual void MouseRelease(const int& cx, const int& cy);
		virtual void MouseStopped(const int& cx, const int& cy);
		virtual void KeyPressed(const KEY& btn);

		//return controller mats
		virtual void SetCombinedViewMat()=0;
		
	};

	typedef std::shared_ptr<CameraController> shrd_Controller;
}

#endif // !CAMERACONTROLLER_H