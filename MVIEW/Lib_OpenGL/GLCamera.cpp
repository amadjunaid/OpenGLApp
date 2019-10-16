#include "GLCamera.h"


namespace mview
{
	GLCamera::GLCamera(const shrd_Camera cam) : GLObject(cam->m_id), GLUBOResource()
	{
		m_cam = cam;
		
		m_UBONameInShader = "UBO_GLCAMERA";
		m_UBOData = UBO_GLCamera(m_cam->Get_viewMat(), m_cam->Get_projMat()->Get(), *m_cam->Get_viewProj());		
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(m_UBOData), &m_UBOData, GL_DYNAMIC_DRAW);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void GLCamera::UpdateView()
	{
		memcpy(&m_UBOData.view, &m_cam->Get_viewMat(), sizeof(m_UBOData.view));
		//Magic function which getst the offset inside the struct of the member
		int bufferOffset = offsetof(UBO_GLCamera, view);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(m_UBOData.view), &m_UBOData.view);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void GLCamera::UpdateProj()
	{
		memcpy(&m_UBOData.proj, &m_cam->Get_projMat()->Get(), sizeof(m_UBOData.proj));
		//Magic function which getst the offset inside the struct of the member
		int bufferOffset = offsetof(UBO_GLCamera, proj);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(m_UBOData.proj), &m_UBOData.proj);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void GLCamera::UpdateViewProj()
	{
		memcpy(&m_UBOData.viewproj, &(*m_cam->Get_viewProj()), sizeof(m_UBOData.viewproj));
		int bufferOffset = offsetof(UBO_GLCamera, viewproj);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(m_UBOData.viewproj), &m_UBOData.viewproj);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	

	void GLCamera::UpdateParam(int name)
	{
		if (!CheckIfBound()) return;
		switch (name)
		{
		case Camera::CAMERA_VIEW:
			UpdateView();			
			break;
		case Camera::CAMERA_PROJ:
			UpdateProj();
			break;	
		default:
			;
		}

		UpdateViewProj();
	}


	GLCamera::~GLCamera()
	{
	}

}