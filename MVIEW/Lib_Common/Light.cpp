#include "Light.h"


namespace mview {
	shrd_Param_vec3 Light::getDiffuse()
	{
		return mp_diffuse;
	}

	float Light::getIntensity()
	{
		return m_intensity;
	}

	Light::Light():SceneObject()
	{
		m_name = std::string("Light_") + std::to_string(m_id);
		
		*m_pose = glm::translate(*m_pose, glm::vec3(2.0f, 2.0f, 2.0f));

		mp_diffuse.reset(new Param_vec3(glm::vec3(1.f, 1.f, 1.f), PM_DIFFUSE));
		m_paramList.push_back(mp_diffuse);
		m_renderMode.reset(new Param<RENDER_MODE>(RENDER_MODE::RM_WIREFRAME, PM_RENDERMODE));
	}

	Light::Light(const glm::vec3 & position, const float & intensity): Light()
	{
		*m_pose = glm::translate(*m_pose, position);
		m_intensity = intensity;
	}


	Light::~Light()
	{
		
	}

}