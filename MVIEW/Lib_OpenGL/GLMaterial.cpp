#include "GLMaterial.h"

namespace mview
{

	GLMaterial::GLMaterial(int matID, const shrd_MaterialLib matLib, const std::vector<int>& texIDs): GLUBOResource()
	{
		g_matID = matID;
		const shrd_Material mat = matLib->GetMaterial(g_matID);

		//Setup UBO according to the shader
		m_UBONameInShader = "UBO_MATERIAL";
		m_UBOData = UBO_GLMaterial(mat->ambient, mat->diffuse, mat->specular, mat->shininess);	
		memcpy(&m_UBOData.diffuseFromTexture, texIDs.data(), sizeof(texIDs[0]) * texIDs.size());
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(m_UBOData), &m_UBOData, GL_DYNAMIC_DRAW);
		gl_check_error();
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

	}


	GLMaterial::~GLMaterial()
	{
	}

	void GLMaterial::UpdateParam(int param)
	{
	}
}
