
#ifndef CONTROLLER_ARCBALL_H
#define CONTROLLER_ARCBALL_H

#include <windows.h>
#include <cmath>
#include "CameraController.h"


namespace mview {
		//Forward declaration
	class Camera;
	typedef std::shared_ptr<Camera> shrd_Camera;
	//************
	//Provides Arcball controller for user inputs
	//************
	
	class DLLEXPORT Controller_ArcBall :
		public CameraController
	{
	protected:
		int m_width = 0;
		int m_height = 0;
		float m_radius = 1.f;
		glm::vec2 m_ballCenter;
		int m_lastCx = 0; int m_lastCy = 0; float m_walkSpeed = 0.f;

		glm::mat4 ab_last = glm::mat4(1.f);
		glm::mat4 ab_next = glm::mat4(1.f);

		glm::vec3 ab_start = glm::vec3(0, 0, 1);
		glm::vec3 ab_curr = glm::vec3(0, 0, 1);
		glm::vec3 ab_out = glm::vec3(1, 0, 0);		

		glm::vec3 SphereCoords_Analytical(float mx, float my);
		void ArcballStart(int cx, int cy);
		void ArcballRotate(int cx, int cy);
		void ArcballTranslate(int cx, int cy);
		void ArcballWalk(int cy);
		

	public:
		bool isDragging = false;
		Controller_ArcBall(shrd_mat4 viewMat_cam, shrd_Param_mat4 viewMatCombined);
		~Controller_ArcBall();

		void MouseClick(const BUTTON& btn, const int& cx, const int& cy);
		void MouseRelease(const int& cx, const int& cy);
		void MouseStopped(const int& cx, const int& cy);

		void Resize(const int& width, const int& height, const glm::vec3& eye, const glm::vec3& up, const glm::mat4& viewMat, const glm::mat4& projMat, const Viewport& viewport);
		void Reset();
		
		void SetCombinedViewMat();

	};

	typedef std::shared_ptr<Controller_ArcBall> shrd_Controller_ArcBall;

}


#endif // !CONTROLLER_ARCBALL_H