#include "Controller_ArcBall.h"
#include "Camera.h"
#include <stdlib.h>
#include <math.h>




namespace mview {
	float MOUSE_SPEED = 16.0f;
	Controller_ArcBall::Controller_ArcBall(shrd_mat4 viewMat_cam, shrd_Param_mat4 viewMatCombined) : CameraController(viewMat_cam, viewMatCombined)
	{
		Reset();			
	}

	Controller_ArcBall::~Controller_ArcBall()
	{
		
	}

	void Controller_ArcBall::MouseClick(const BUTTON& btn, const int& cx, const int& cy)
	{
		if (isDragging) {
			switch (btn)
			{
			case BUTTON::LEFT:				
				ArcballRotate(cx, m_height - cy);
				break;
			case BUTTON::MIDDLE:				
				ArcballTranslate(cx, m_height - cy);
				m_lastCx = cx; m_lastCy = m_height - cy;
				break;
			case BUTTON::RIGHT:
				ArcballWalk( m_height - cy );
				m_walkSpeed = float(m_height - cy);
				break;
			default:
				break;
			}						
		}
		else {
			isDragging = true;
			switch (btn)
			{
			case BUTTON::LEFT:				
				ArcballStart(cx, m_height - cy);
				break;
			case BUTTON::MIDDLE:
				m_lastCx = cx; m_lastCy = m_height - cy;
				break;
			case BUTTON::RIGHT:
				m_walkSpeed = float(m_height - cy);
				break;
			default:
				break;
			}			
		}
	}

	void Controller_ArcBall::MouseRelease(const int& cx, const int& cy)
	{
		//m_TransformationMat = glm::translate(m_TransformationMat, glm::vec3(0.f, 0.f, 0.f));
		isDragging = false;
		//std::cout << "MouseReleasedNow" << std::endl;
	}

	void Controller_ArcBall::MouseStopped(const int & cx, const int & cy)
	{
		//m_TransformationMat = glm::translate(m_TransformationMat, glm::vec3(0.f, 0.f, m_walkSpeed));
	}

	void Controller_ArcBall::Resize(const int& width, const int& height, const glm::vec3& eye, const glm::vec3& up, const glm::mat4& viewMat, const glm::mat4& projMat, const Viewport& viewport)
	{
		m_width = width; m_height = height;
		m_radius = glm::min((float)m_height / 2.f, (float)m_width / 2.f);
		m_ballCenter = glm::vec2((float)m_width / 2.f, (float)m_height / 2.f);
	}

	//Alternate Method to map mouse coordinates to screen. Using mathematical formula of sphere.
	glm::vec3 Controller_ArcBall::SphereCoords_Analytical(float mx, float my)
	{
		glm::vec3 ballMouse;
		register float mag2;
		//Normalize the mouse point for easy comparison
		ballMouse.x = (mx - m_ballCenter.x) / m_radius;
		ballMouse.y = (my - m_ballCenter.y) / m_radius;

		mag2 = ballMouse.x*ballMouse.x + ballMouse.y*ballMouse.y; //Distance of mouse point from the center

		if (mag2 > 1.f) {  //Clicked point is outside the sphere so it is constrained by division by magnitude
			float scale = 1.f / sqrtf(mag2);
			ballMouse.x *= scale; ballMouse.y *= scale;
			ballMouse.z = 0.f;
		}
		else {
			ballMouse.z = sqrtf(1 - mag2);   //z = sqrt(1-x^2 - y^2)... from sphere equation
		}

		return ballMouse;
	}

	// reset the arcball
	void Controller_ArcBall::Reset()
	{
		SetCombinedViewMat();				
	}

	// begin arcball rotation
	void Controller_ArcBall::ArcballStart(int mx, int my)
	{
		// saves a copy of the current rotation for comparison
		ab_last = m_rotationMat;		
		ab_start = SphereCoords_Analytical((float)mx, (float)my);
	}

	// update current arcball rotation
	void Controller_ArcBall::ArcballRotate(int mx, int my)
	{
		ab_curr = SphereCoords_Analytical((float)mx, (float)my);
		if (ab_curr == ab_start)
		{ // avoid potential rare divide by tiny
			m_rotationMat = ab_last;
			SetCombinedViewMat();
			return;
		}

		// use a dot product to get the angle between them
		// use a cross product to get the vector to rotate around
		float cos2a = glm::dot(ab_start, ab_curr);
		float sina = sqrt((1.0f - cos2a)*0.5f);
		float cosa = sqrt((1.0f + cos2a)*0.5f);
		glm::vec3 cross = glm::normalize(glm::cross(ab_start,ab_curr)) * sina;
		float* tmp= new float[16];
		QuatToMat4(ab_next, cross.x, cross.y, cross.z, cosa);
		
		// update the rotation matrix
		m_rotationMat = ab_next * ab_last;	
		SetCombinedViewMat();
		
		delete tmp;
	}

	void Controller_ArcBall::ArcballTranslate(int cx, int cy)
	{
		glm::vec3 translation = glm::vec3((float)(cx - m_lastCx) / (float)m_width, (float)(cy - m_lastCy) / (float)m_height, 0.f) * MOUSE_SPEED;						
		m_translationVec += glm::vec3( -translation );
		SetCombinedViewMat();
		//std::cout << "Translation delta: " << translation.x << " ," << translation.y << std::endl;		
	}

	void Controller_ArcBall::ArcballWalk(int cy)
	{
		float translation = (float)(cy - m_walkSpeed) / (float)m_height;
		glm::mat4 mat = *m_combinedViewMat;
		glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);

		m_translationVec += (-translation * forward) * MOUSE_SPEED;
		SetCombinedViewMat();
		//std::cout << "Walk delta: " << translation.z << std::endl;
	}

	void Controller_ArcBall::SetCombinedViewMat()
	{
		
		glm::mat4 rotation = m_rotationMat;
		glm::mat4 transform = glm::mat4(rotation[0].x, rotation[0].y, rotation[0].z, rotation[0].w,
			rotation[1].x, rotation[1].y, rotation[1].z, rotation[1].w,
			rotation[2].x, rotation[2].y, rotation[2].z, rotation[2].w,
			-m_translationVec.x, -m_translationVec.y, -m_translationVec.z, 1.f);

		transform[3] = glm::vec4((*m_viewMat_cam)[0] * transform[3].x +
			(*m_viewMat_cam)[1] * transform[3].y +
			(*m_viewMat_cam)[2] * transform[3].z);
		transform[3].w = 1.f;

		*m_combinedViewMat = *m_viewMat_cam * transform;
		//m_isMoved = false;

	}
}