#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <Camera.h>
#include "GLObject.h"
#include "GLUBOResource.h"

namespace mview
{
	class GLCamera : public GLObject, public GLUBOResource
	{
	public:
		struct UBO_GLCamera
		{
			glm::mat4 view;
			glm::mat4 proj;
			glm::mat4 viewproj;
			UBO_GLCamera() {}
			UBO_GLCamera(glm::mat4 view_, glm::mat4 proj_, glm::mat4 viewProj_)
			{
				memcpy(&view, &view_, sizeof(view));
				memcpy(&proj, &proj_, sizeof(proj));
				memcpy(&viewproj, &viewProj_, sizeof(viewproj));
			}
		} m_UBOData;

		shrd_Camera m_cam;

		void UpdateView();
		void UpdateProj();
		void UpdateViewProj();
	public:
		
		GLCamera( const shrd_Camera );
		void UpdateParam(int name);
		~GLCamera();
	};

	typedef std::shared_ptr<GLCamera> shrd_GLCamera;

}
#endif // !GLCAMERA_H

