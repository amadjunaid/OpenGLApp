
#ifndef LIGHT_H
#define LIGHT_H

#include "SceneObject.h"
#include "CommonUtils.h"
#include "TriangleMesh.h"
#include "Param.h"

namespace mview {
	//************
	//Base class to derive lights like poin light, directional etc
	//************
	class DLLEXPORT Light: public SceneObject
	{
	protected:
		float m_intensity = 50.f;		
		shrd_Param_vec3 mp_diffuse;
		//To render light in the scene
		

	public:
		shrd_Param_vec3 getDiffuse();
		float getIntensity();
		Light();
		Light(const glm::vec3& position, const float& intensity);
		virtual ~Light();
		
		enum {PM_DIFFUSE = SceneObject::COUNT, PM_INTENSITY, COUNT};
	};

	typedef std::shared_ptr<Light> shrd_Light;
	typedef std::vector<shrd_Light> LightList;
	typedef std::shared_ptr<LightList> shrd_LightList;
}

#endif // !LIGHT_H

