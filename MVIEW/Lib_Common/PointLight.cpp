#include "PointLight.h"



namespace mview
{
	PointLight::PointLight(): Light()
	{
		Init();
	}

	PointLight::PointLight(const glm::vec3 & position, const float & intensity): Light(position, intensity)
	{
		Init();
	}

	void PointLight::Init()
	{
		m_type = MOBJECT_TYPE::POINTLIGHT;
		m_initialized = true;
		shrd_TriangleMesh triMesh(new TriangleMesh());

		triMesh->loadObjWithoutMaterial("..\\Data\\OwnTypeMeshes\\PointLight.obj");
		m_meshes.push_back(triMesh);
		std::cout << "SceneObject POSE " << PointLight::PM_POSE << std::endl;
		std::cout << "SceneObject COUNT " << SceneObject::COUNT << std::endl;
		std::cout << "Light DIFFUSE " << PointLight::PM_DIFFUSE << std::endl;
		std::cout << "Light COUNT " << PointLight::COUNT << std::endl;

	}


	PointLight::~PointLight()
	{
#ifdef _DEBUG
		Logger::Message(LOG_INFO, m_name + " deleted.");
#endif		
	}

}