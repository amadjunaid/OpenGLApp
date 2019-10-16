#include "SceneObject.h"


namespace mview {
	SceneObject::SceneObject(): MObject()
	{
		m_pose.reset(new glm::mat4(1.f));

		m_renderMode.reset(new Param<RENDER_MODE>(RM_NORMAL, PM_RENDERMODE));


		m_paramList.push_back(m_renderMode);
	}


	SceneObject::~SceneObject()
	{
	}

	shrd_mat4 SceneObject::getPose()
	{
		return m_pose;
	}

	glm::vec3 SceneObject::getPosition()
	{
		return glm::vec3((*m_pose)[3].x, (*m_pose)[3].y, (*m_pose)[3].z);
	}

	const std::vector<shrd_TriangleMesh>& SceneObject::getTriMeshes()
	{
		return m_meshes;
	}
}
