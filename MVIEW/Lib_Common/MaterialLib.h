#pragma once
#ifndef MATERIALLIB_H
#define MATERIALLIB_H
#include "CommonUtils.h"

namespace mview
{
	enum MATERIAL_TYPE {MATERIAL_COLORED, MATERIAL_TEXTURED};
	struct DLLEXPORT Material {
		std::string name = "";
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		float shininess;
		MATERIAL_TYPE type = MATERIAL_COLORED;
		Material()
		{
			ambient = glm::vec4(0.5f);
			diffuse = glm::vec4(0.8f);
			specular = glm::vec4(1.f);
			shininess = 32.f;
			type = MATERIAL_COLORED;
		}

		Material(const glm::vec4& ambient_, const glm::vec4& diffuse_, const glm::vec4& specular_, const float& shininess_):
			ambient(ambient_), diffuse(diffuse_), specular(specular_), shininess(shininess_)
		{
		}
	};
	typedef std::shared_ptr<Material> shrd_Material;

	//************
	//Provides material library
	//Does not handle changes in the material for now since no interface is available in the UI
	//************
	class DLLEXPORT MaterialLib
	{
	protected:
		std::vector<shrd_Material> m_materials;
	public:
		MaterialLib();
		int AddMaterials(const shrd_Material mat);
		int AddMaterialFrom_MtlFile(const std::string& filePath, const std::string& MtlName);
		bool ReadMaterial(FILE* file, shrd_Material& mat);
		void DeleteMaterial(int idx);
		const shrd_Material GetMaterial(int idx);
		~MaterialLib();
	};

	typedef std::shared_ptr<MaterialLib> shrd_MaterialLib;
}
#endif // !MATERIALLIB_H


