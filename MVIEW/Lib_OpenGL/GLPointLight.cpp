#include "GLPointLight.h"
#include "GLError.h"



namespace mview
{
	/*GLPointLight::GLPointLight(): GLUBOResource()
	{
		
	}*/

	GLPointLight::GLPointLight(shrd_PointLight pointLight): GLUBOResource(), GLObject(pointLight->m_id)
	{
		m_pointLight = pointLight;

		//Setup UBO according to the shader
		m_UBONameInShader = "UBO_GLPOINTLIGHT";
		m_UBOData = UBO_GLPointLight(m_pointLight->getPosition(),m_pointLight->getDiffuse()->Get(), m_pointLight->getIntensity());
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(m_UBOData), &m_UBOData, GL_DYNAMIC_DRAW);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);		
	}


	GLPointLight::~GLPointLight()
	{
	}

	void GLPointLight::UpdateParam(int param)
	{
		if (!CheckIfBound()) return;
		switch (param)
		{
		case Light::PM_DIFFUSE:
			UpdateDiffuse();
			break;
		case Light::PM_POSE:
			UpdatePosition();
			break;
		case Light::PM_INTENSITY:
			UpdateIntensity();
			break;
		default:
			;
		}
	}

	void GLPointLight::UpdatePosition()
	{
		memcpy(m_UBOData.position, &m_pointLight->getPosition(), sizeof(m_pointLight->getPosition()));
		//Magic function which getst the offset inside the struct of the member
		int bufferOffset = offsetof(UBO_GLPointLight, position);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(m_UBOData.position), m_UBOData.position);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void GLPointLight::UpdateDiffuse()
	{
		memcpy(m_UBOData.diffuse, &m_pointLight->getDiffuse()->Get(), sizeof(m_pointLight->getDiffuse()));
		int bufferOffset = offsetof(UBO_GLPointLight, diffuse);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(m_UBOData.diffuse), m_UBOData.diffuse);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void GLPointLight::UpdateIntensity()
	{
		m_UBOData.intensity = m_pointLight->getIntensity();
		int bufferOffset = offsetof(UBO_GLPointLight, intensity);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, bufferOffset, sizeof(m_UBOData.intensity), &m_UBOData.intensity);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

}