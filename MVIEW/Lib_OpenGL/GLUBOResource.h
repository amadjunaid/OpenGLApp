#ifndef GLUBORESOURCE_H
#define GLUBORESOURCE_H
#include "CommonUtils_Lib_OpenGL.h"
#include "GLShader.h"
#include "GLError.h"

//BPI for the first uniform block in the shader which only contains information about other binding blocks i.e. number of objects etc.
#define UBOInfoData_BPI 0

namespace mview
{
	enum UBOType {UBO_GLPOINTLIGHT, UBO_GLMATERIALS, UBOTYPES_COUNT};

	//Struct to load info for other UBOs e.g. count etc.. elements should match the order in UBOType
	struct UBOInfoData {
		int numPointLights = 0;
		int numMaterials = 0;
	};

	//************
	//Provides GL Uniform Buffer Object functionality. Loads the data to a UBO and contains the bpi to load it to a shader
	//************
	class GLUBOResource
	{
	protected:
		//Ensures that a unique BPI is used for every Uniform Block in the shader
		static GLuint m_countBPI;
		std::string m_UBONameInShader = "";
		bool CheckIfBound();

	public:
		GLuint m_bpi = 0;
		GLuint m_ubo = 0;
		bool m_isBound = false;
		void BindToShader(shrd_GLShaderTechnique shader, const int& index);
		void BindToShaderNonIndexed(shrd_GLShaderTechnique shader);
		
		GLUBOResource();
		virtual ~GLUBOResource();
	};

	typedef std::shared_ptr<GLUBOResource> shrd_GLUBOResource;
}


#endif // !GLUBOResource
