#pragma once
#include "CameraController.h"

#ifndef CONTROLLERWALKER_H
#define CONTROLLERWALKER_H

namespace mview
{

	class Controller_Walker :public CameraController
	{
	private:
		//float m_positionX, m_positionY, m_positionZ;

		glm::vec3 m_rotation = glm::vec3(0.f);
		//float m_rotationX, m_rotationY, m_rotationZ;

		float m_frameTime;

		float m_forwardSpeed, m_backwardSpeed;
		float m_upwardSpeed, m_downwardSpeed;
		float m_leftTurnSpeed, m_rightTurnSpeed;
		float m_lookUpSpeed, m_lookDownSpeed;

		/*void MoveForward(bool);
		void MoveBackward(bool);
		void MoveUpward(bool);
		void MoveDownward(bool);
		void TurnLeft(bool);
		void TurnRight(bool);
		void LookUpward(bool);
		void LookDownward(bool);*/
		void MouseMove(int cx, int cy);

	protected:
		int m_width = 0;
		int m_height = 0;
		int m_lastCx = 0; int m_lastCy = 0; float m_walkSpeed = 0.f;

	public:
		bool isDragging = false;
		Controller_Walker(shrd_mat4 viewMat_cam, shrd_Param_mat4 viewMatCombined);
		~Controller_Walker();
		void Resize(const int& width, const int& height, const glm::vec3& eye, const glm::vec3& up, const glm::mat4& viewMat, const glm::mat4& projMat, const Viewport& viewport);

		void KeyPressed(const KEY& key);
		void MouseClick(const BUTTON& btn, const int& cx, const int& cy);
		void MouseRelease(const int& cx, const int& cy);

		void SetCombinedViewMat();
	};

}
#endif // !CONTROLLERWALKER_H

