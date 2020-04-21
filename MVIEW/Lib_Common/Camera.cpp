#include "Camera.h"

#include "Controller_ArcBall.h"
#include "Controller_Walker.h"

namespace mview {
	float ZOOM_SPEED = 0.2f;
	Camera::Camera(): MObject()//: m_controller(controller)
	{
		// Initial position : on +Z
		glm::vec3 position = glm::vec3(0.f, 5.f, 50.f);
		
		// Initial Field of View
		m_fov = 45.0f;

		// Camera matrix
		m_viewMat.reset(new glm::mat4(1.0));
		*m_viewMat = glm::lookAt(
			position, 
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
		
		m_projMat.reset(new Param_mat4(glm::mat4(glm::perspective(glm::radians(m_fov), 4.0f / 3.0f, m_near, m_far)), CAMERA_PROJ));
		m_viewProj.reset(new glm::mat4( m_projMat->Get() * *m_viewMat));
		
		m_name = std::string("Camera_") + std::to_string(m_id);
		m_type = MOBJECT_TYPE::CAMERA;
		m_initialized = true;

		m_combinedViewMat.reset(new Param_mat4(*m_viewMat, CAMERA_VIEW, nullptr));

		m_viewController.reset(new mview::Controller_ArcBall(m_viewMat, m_combinedViewMat));
		//m_viewController.reset(new mview::Controller_Walker(m_viewMat, m_combinedViewMat));
		m_paramList.push_back(m_combinedViewMat);
		m_paramList.push_back(m_projMat);
	}

	void Camera::Resize(float fov, int width, int height, float n, float f)
	{
		m_fov = fov; m_near = n; m_far = f;
		*m_projMat = glm::mat4(glm::perspective(glm::radians(m_fov), (float)width / (height > 0 ? (float)height : 1.0f), m_near, m_far));
		m_viewport = Viewport( 0 , 0, width, height );
		if(m_viewController)
			m_viewController->Resize(width, height, Get_position(), Get_up(), *m_viewMat, m_projMat->Get(), m_viewport);
		*m_viewProj = m_projMat->Get() * m_combinedViewMat->Get();
	}

	void Camera::Zoom(const float& degrees, const int& width, const int& height)
	{
		float new_fov = m_fov + (ZOOM_SPEED * degrees);
		if (new_fov > 0 && new_fov < 170) {
			m_fov = new_fov;
			//std::cout << "FOV: " << m_fov << std::endl;
			*m_projMat = glm::mat4(glm::perspective(glm::radians(m_fov), (float)width / (height > 0 ? (float)height : 1.0f), m_near, m_far));
			*m_viewProj = m_projMat->Get() * m_combinedViewMat->Get();
		}
	}

	void Camera::ChangeController(CONTROLLERS controller, const int& width, const int& height)
	{
		switch (controller)
		{
		case(CONTROLLER_ARCBALL):
		{
			m_viewController.reset(new mview::Controller_ArcBall(m_viewMat, m_combinedViewMat));			
			break;
		}
		case(CONTROLLER_WALKER):
		{
			m_viewController.reset(new mview::Controller_Walker(m_viewMat, m_combinedViewMat));
			break;
		}

		
		default:
			break;

		}

		m_viewController->Resize(width, height, Get_position(), Get_up(), *m_viewMat, m_projMat->Get(), m_viewport);
	}
		
	glm::mat4 Camera::Get_viewMat()
	{
		//if (/*m_viewController->m_isMoved*/true) {
		//	
		//	glm::mat4 transform = m_viewController->GetTransformationMat();
		//	transform[3] = glm::vec4( glm::vec3(Get_right()*transform[3].x +
		//		Get_up()*transform[3].y +
		//		Get_dir()*transform[3].z),
		//		1.f);
		//	
		//	m_actualView->Set( *m_viewMat * transform);
		//}
		//
		*m_viewProj = m_projMat->Get() * m_combinedViewMat->Get();
		return *m_combinedViewMat;
	}

	shrd_Param_mat4 Camera::Get_projMat()
	{
		return m_projMat;
	}

	shrd_mat4 Camera::Get_viewProj()
	{
		return m_viewProj;
	}
	
	glm::vec3 Camera::Get_up()
	{
		return glm::vec3((*m_viewMat)[1].x, (*m_viewMat)[1].y, (*m_viewMat)[1].z);
	}

	glm::vec3 Camera::Get_right()
	{
		return glm::vec3((*m_viewMat)[0].x, (*m_viewMat)[0].y, (*m_viewMat)[0].z);
	}

	glm::vec3 Camera::Get_dir()
	{
		return glm::vec3((*m_viewMat)[2].x, (*m_viewMat)[2].y, (*m_viewMat)[2].z);
	}

	glm::vec3 Camera::Get_position()
	{
		return -1.f*glm::vec3((*m_viewMat)[3].x, (*m_viewMat)[3].y, (*m_viewMat)[3].z);
	}

	const Viewport & Camera::Get_viewport()
	{
		return m_viewport;
	}

	shrd_Controller Camera::Get_controller()
	{
		if(m_viewController)
			return m_viewController;
		return nullptr;
	}

	Camera::~Camera()
	{
		
	}
}