#ifndef CAMERA_H
#define CAMERA_H

#include "CommonUtils.h"
#include "Controller_ArcBall.h"
#include "MObject.h"
#include "Param.h"
#include "Param.h"


namespace mview {

	struct Viewport {
		int x; int y; int width; int height;
		Viewport() {
			x = 0; y = 0; width = 0; height = 0;
		}
		Viewport(int _x, int _y, int _width, int _height) {
			x = _x; y = _y; width = _width; height = _height;
		}
	};

	//************
	//Generic perspective camera for the scene
	//************
	class DLLEXPORT Camera: public MObject
	{

	private:
		//Containers to hold the state
		volatile bool m_isMoved = false;
		shrd_mat4 m_viewMat;
		shrd_Param_mat4 m_combinedViewMat;

		shrd_Param_mat4 m_projMat;
		shrd_mat4 m_viewProj;
		Viewport m_viewport;

		// Initial Field of View
		float m_near = 0.1f;
		float m_far = 100.f;
		float m_fov;

		// CameraController
		shrd_Controller m_viewController;

		
	public:
		Camera();
		void Resize(float fov, int width, int height, float n, float f);
		void Zoom(const float& degrees, const int& width, const int& height);
		void ChangeController(CONTROLLERS controller, const int& width, const int& height);

		glm::mat4 Get_viewMat();
		shrd_Param_mat4 Get_projMat();
		shrd_mat4 Get_viewProj();		

		glm::vec3 Get_up();
		glm::vec3 Get_right();
		glm::vec3 Get_dir();
		glm::vec3 Get_position();
		const Viewport& Get_viewport();

		//For handling input
		shrd_Controller Get_controller();		

		~Camera();

		//Params
		enum { CAMERA_VIEW, CAMERA_PROJ, CAMERA_VIEWPROJ };
	};

	typedef std::shared_ptr<Camera> shrd_Camera;
}

#endif // !CAMERA_H
