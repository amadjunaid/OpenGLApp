
#ifndef GLPOINTLIGHT_H
#define GLPOINTLIGHT_H

#include "CommonUtils_Lib_OpenGL.h"
#include <PointLight.h>
#include "GLUBOResource.h"
#include "GLObject.h"

namespace mview
{
	//************
	//Open GL point light
	//************
	class GLPointLight: public GLUBOResource, public GLObject
	{
	protected:
		//Struct used to copy data to the UBO, mirrors the Uniform Block in the shader
		struct UBO_GLPointLight
		{
			float position[4];
			float diffuse[4];
			float intensity;
			float pad[3];
			UBO_GLPointLight() {}
			UBO_GLPointLight(glm::vec3 position_, glm::vec3 diffuse_, float intensity_)
			{
				memcpy(position, &position_, sizeof(position_)); position[3] = 1.f;
				//position[0] = pos.x; position[1] = pos.y; position[2] = pos.z; position[3] = 1.f;
				memcpy(diffuse, &diffuse_, sizeof(diffuse_)); diffuse[3] = 0.f;
				//diffuse[0] = diffuse_.x; diffuse[1] = diffuse_.y; diffuse[2] = diffuse_.z; diffuse_[3] = 0.f;
				intensity = intensity_;
			}
		} m_UBOData;

		//Update functions, need to be implemented for all struct members separately if needed
		void UpdatePosition();
		void UpdateDiffuse();
		void UpdateIntensity();
	public:
		shrd_PointLight m_pointLight = nullptr;
		
		//GLPointLight();
		GLPointLight(shrd_PointLight pointLight);
		~GLPointLight();		

		void UpdateParam(int param);
		
	};

	typedef std::shared_ptr<GLPointLight> shrd_GLPointLight;
	typedef std::vector<shrd_GLPointLight> GLPointLightList;
	typedef std::shared_ptr<GLPointLightList> shrd_GLPointLightList;

	typedef SpecialCompare<shrd_GLPointLight> CompareGLPointLight;
}
#endif // !GLPOINTLIGHT_H