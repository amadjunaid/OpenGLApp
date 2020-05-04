#include "MaterialLib.h"


namespace mview {
	MaterialLib::MaterialLib()
	{
		//To add one generic material which can be used of an error on material reading from file
		m_materials.push_back(shrd_Material(new Material()));
	}

	size_t MaterialLib::AddMaterials(const shrd_Material mat)
	{
		m_materials.push_back(mat);
		return m_materials.size() - 1;
	}

	size_t MaterialLib::AddMaterialFrom_MtlFile(const std::string& filePath, const std::string& MtlName)
	{
		FILE * file = fopen(filePath.c_str(), "r");

		//check if file is opened and can be loaded
		if (file == NULL) {
			Logger::Message(LOG_SEVERITY::LOG_ERROR, "Impossible to open material file: " + filePath);
			return 0;
		}

		while (1) {
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				Logger::Message(LOG_SEVERITY::LOG_ERROR, "No material found in material file: " + filePath);
				return 0; // EOF = End Of File. Quit the loop.
			}

			if (strcmp(lineHeader, "newmtl") == 0) {
				
				char matName[128];
				fscanf(file, "%s", matName);
				if (strcmp(MtlName.c_str(), matName) == 0) {
					shrd_Material mat;
					if (ReadMaterial(file, mat))
					{
						return AddMaterials(mat);
					}
					else
					{
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "Error in reading material '"+ MtlName +"' from file: " + filePath);
						return 0; 
					}
				}
			}
		}
		return 0;
	}

	bool MaterialLib::ReadMaterial(FILE * file, shrd_Material& mat)
	{
		bool noFormatError = true;
		while (1)
		{
			char lineHeader[128];
			long line = ftell(file);
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				break;
			}

			else if (strcmp(lineHeader, "Ka") == 0) {
				float r, g, b;
				int matches = fscanf(file, "%f %f %f", &r, &g, &b);
				if (matches != 3) { 
					Logger::Message(LOG_SEVERITY::LOG_ERROR, "Material format error for ambient component."); noFormatError = false;
				}
				else mat->ambient = glm::vec4(r, g, b, 1.);
			}
			
			else if (strcmp(lineHeader, "Kd") == 0) {
				float r, g, b;
				int matches = fscanf(file, "%f %f %f", &r, &g, &b);
				if (matches != 3) { 
					Logger::Message(LOG_SEVERITY::LOG_ERROR, "Material format error for diffuse component."); noFormatError = false;
				}
				else mat->diffuse = glm::vec4(r, g, b,1.);
			}

			else if (strcmp(lineHeader, "Ks") == 0) {
				float r, g, b;
				int matches = fscanf(file, "%f %f %f", &r, &g, &b);
				if (matches != 3) { 
					Logger::Message(LOG_SEVERITY::LOG_ERROR, "Material format error for specular component."); noFormatError = false;
				}
				else mat->specular = glm::vec4(r, g, b, 1.f );
			}

			else if (strcmp(lineHeader, "Ns") == 0) {
				float s = 1.f;
				int matches = fscanf(file, "%f", &s);
				if (matches != 1) { 
					Logger::Message(LOG_SEVERITY::LOG_ERROR, "Material format error for specular component."); noFormatError = false;
				}
				else mat->shininess = s;
			}
			else if (strcmp(lineHeader, "newmtl") == 0)
			{
				fseek(file, line, SEEK_SET);	
				break;
			}
		}

		return noFormatError;
	}

	void MaterialLib::DeleteMaterial(int idx)
	{
		m_materials.erase(m_materials.begin() + idx);
	}

	const shrd_Material MaterialLib::GetMaterial(size_t idx)
	{
		if(idx<m_materials.size())
			return m_materials.at(idx);
		else 
			return m_materials.at(0);
	}


	MaterialLib::~MaterialLib()
	{
	}
}
