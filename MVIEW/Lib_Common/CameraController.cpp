#include "CameraController.h"
#include "SceneManager.h"

namespace mview {
	CameraController::CameraController(shrd_mat4 viewMat_cam, shrd_Param_mat4 viewMatCombined)
	{
		m_combinedViewMat = viewMatCombined;
		m_viewMat_cam = viewMat_cam;
	}	

	CameraController::~CameraController()
	{
	}
	void CameraController::Reset()
	{
	}
	void CameraController::Resize(const int& width, const int& height, const glm::vec3& eye, const glm::vec3& up, const glm::mat4& viewMat, const glm::mat4& projMat, const Viewport& viewport)
	{
	}
	void CameraController::MouseClick(const BUTTON & btn, const int & cx, const int & cy)
	{
	}
	void CameraController::MouseRelease(const int & cx, const int & cy)
	{
	}
	void CameraController::MouseStopped(const int & cx, const int & cy)
	{
	}
	void CameraController::KeyPressed(const KEY & key)
	{
		// Handle the input.
		switch (key) {
		case KEY::A:
			Logger::Message("Pressed Key: A");
			break;
		case KEY::D:
			Logger::Message("Pressed Key: D");
			break;
		case KEY::W:
			Logger::Message("Pressed Key: W");
			break;
		case KEY::S:
			Logger::Message("Pressed Key: S");
			break;
		case KEY::E:
			Logger::Message("Pressed Key: E");
			break;
		case KEY::Q:
			Logger::Message("Pressed Key: Q");
			break;
		case KEY::C:
			Logger::Message("Pressed Key: C");
			break;
		case KEY::Y:
			Logger::Message("Pressed Key: Y");
			break;
		default:
			break;
		}
	}

	/*const glm::mat4 & CameraController::GetTransformationMat()
	{
		return glm::mat4(m_RotationMat[0],
			m_RotationMat[1],
			m_RotationMat[2],
			m_translationVec);
	}*/

}