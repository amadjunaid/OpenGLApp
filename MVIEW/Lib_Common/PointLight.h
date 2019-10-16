
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace mview
{
	//************
	//Represents a point light present in the scene. Contains the visual representation i.e. a tri mesh as well as properties
	//for this light.
	//************
	class DLLEXPORT PointLight: public Light
	{
	public:
		//enum CHANGED {POSITION, PM_DIFFUSE, PM_INTENSITY};

		inline PointLight();
		PointLight(const glm::vec3& position, const float& intensity);
		void Init();
		virtual ~PointLight();
	};

	typedef std::shared_ptr<PointLight> shrd_PointLight;

}

#endif // !POINTLIGHT_H
