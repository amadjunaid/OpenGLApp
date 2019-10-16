#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include "CommonUtils_Lib_OpenGL.h"


namespace mview {
	enum SHADER_STATUS{NICHTS, HASCODE, COMPILED, LINKED};
	enum SHADER_TYPE{SHADER_VERTEX, SHADER_FRAGMENT, SHADER_GEOMETRY, SHADER_TESSELATION, SHADER_COMPUTE, ST_COUNT, SHADER_UNKNOWN};
	
	enum TECHNIQUE_TYPE {DRAW, COMPUTATION};


	//************
	//Used to build complete shader program to draw or compute
	//************
	class GLShaderTechnique {
	private:
		//Used to handle individual gl shaders i.e. vertex, fragement etc
		struct GLShader {
			GLuint m_id;
			int m_status;
			int m_startLine;
			GLShader(GLuint id) : m_id(id), m_status(0), m_startLine(0)
			{
			}
			~GLShader()
			{
				if (m_id)
					glDeleteShader(m_id);
			}
		};

		std::string m_filePath;
		
	protected:

	public:
		GLuint m_id;
		int m_type;
		GLShaderTechnique();
		GLShaderTechnique(std::string file_path);
		~GLShaderTechnique();
		bool ResetTechnique();
		int DecideShaderType(const char *);
		int getGLShaderEnum(int);
	};

	typedef std::shared_ptr<GLShaderTechnique> shrd_GLShaderTechnique;
}
#endif // !SHADER_H