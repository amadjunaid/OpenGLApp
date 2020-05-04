#pragma once
#ifndef GLMATERIAL_H
#define GLMATERIAL_H

#include "CommonUtils_Lib_OpenGL.h"
#include <MaterialLib.h>
#include "GLUBOResource.h"
#include "GLObject.h"
#include "GLTexture.h"

namespace mview
{
	//************
	//Open GL materials
	//************
	class GLMaterial: public GLUBOResource
	{
	protected:
		//Struct used to copy data to the UBO, mirrors the Uniform Block in shader
		struct UBO_GLMaterial
		{
			float ambient[4];
			float diffuse[4];
			float specular[4];			
			float shininess;
			int diffuseFromTexture;
			int specularFromTexture;
			int pad = 0;
			//float pad[3];
			UBO_GLMaterial(){}
			UBO_GLMaterial(glm::vec4 ambient_, glm::vec4 diffuse_, glm::vec4 specular_, float shininess_){
				memcpy(ambient, &ambient_, sizeof(ambient)); //ambient[3] = 1.f;
				memcpy(diffuse, &diffuse_, sizeof(diffuse)); //diffuse[3] = 1.f;
				memcpy(specular, &specular_, sizeof(specular)); //specular[3] = shininess_;
				shininess = shininess_;
			}
		}m_UBOData;

	public:
		size_t g_matID;
		shrd_MaterialLib g_matLib;
		GLMaterial(size_t matID, const shrd_MaterialLib, const std::vector<int>& texIDs);
		~GLMaterial();
		void UpdateParam(int param);
	};

	typedef std::shared_ptr<GLMaterial> shrd_GLMaterial;
	
	typedef std::vector<shrd_GLMaterial> GLMaterialList;

	

}
#endif // !GLMATERIAL_H

