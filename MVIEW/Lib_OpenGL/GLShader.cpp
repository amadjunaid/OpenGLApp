#include "GLShader.h"

#include <stdio.h>
#include <algorithm>

#include <stdlib.h>

#include <sstream>

#include "GLError.h"

namespace mview {
	GLShaderTechnique::GLShaderTechnique()
	{
		m_id = 0;
		m_type = -1;
	}

	GLShaderTechnique::GLShaderTechnique(std::string file_path) : GLShaderTechnique()
	{		
		m_filePath = file_path;
		ResetTechnique();
	}

	GLShaderTechnique::~GLShaderTechnique()
	{
		glDeleteProgram(m_id);
	}

	int GLShaderTechnique::DecideShaderType(const char* label)
	{
		if (strcmp(label, "/*<--Compute-->*/") == 0)
			return SHADER_COMPUTE;
		else if (strcmp(label, "/*<--Vertex-->*/") == 0)
			return SHADER_VERTEX;
		else if (strcmp(label, "/*<--Geometry-->*/") == 0)
			return SHADER_GEOMETRY;
		else if (strcmp(label, "/*<--Fragment-->*/") == 0)
			return SHADER_FRAGMENT;
		else return SHADER_UNKNOWN;
	}

	int GLShaderTechnique::getGLShaderEnum(int type)
	{
		switch (type) {
		case SHADER_COMPUTE:
			return GL_COMPUTE_SHADER;
			break;
		case SHADER_VERTEX:
			return GL_VERTEX_SHADER;
			break;
		case SHADER_GEOMETRY:
			return GL_GEOMETRY_SHADER;
			break;
		case SHADER_FRAGMENT:
			return GL_FRAGMENT_SHADER;
			break;
		default:
			return GL_FALSE;
			;
		}
	}

	bool GLShaderTechnique::ResetTechnique()
	{
		
		std::vector<GLShader> internalShaders(SHADER_TYPE::ST_COUNT, GLShader(0));
		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Read the Vertex Shader code from the file and copying to shader objects
		std::string shaderCode;
		std::ifstream shaderStream(m_filePath.c_str(), std::ios::in);
		if (shaderStream.is_open()) {
			int lineNum = -1;
			std::string Line = "";			
			while ( getline(shaderStream, Line ) ) 
			{
				lineNum++;
				int startLine = 0;
				std::string shaderLabel = "";
				bool hasSomeCode = false;
				if (strcmp(Line.substr(0, 5).c_str(), "/*<--") == 0 &&
					strcmp(Line.substr(Line.length() - 5, Line.length() - 1).c_str(), "-->*/") == 0) {
					shaderLabel = Line;
					startLine = lineNum;
					//Copying current block of shader code
					while (getline(shaderStream, Line)) {
						lineNum++;
						if (strcmp(Line.c_str(), "/*<---->*/") == 0) {
							hasSomeCode = true;
							break;
						}
						//Handle header file in shader
						else if (strcmp(Line.substr(0, 11).c_str(), "/*#include<") == 0)
						{
							std::string headerFile = GetDirPath(m_filePath) + Line.substr(11, Line.length() - 14);
							std::ifstream headerStream(headerFile.c_str(), std::ios::in);
							
							shaderCode += CopyFileToString(headerFile);
						}

						else
						{
							shaderCode += "\n" + Line;
						}
						
					}
				} 
				//Copy shader code				
				int shaderType = DecideShaderType(shaderLabel.c_str());
				if (hasSomeCode) {
					if (shaderType == SHADER_UNKNOWN) {
						Logger::Message(LOG_ERROR, "Wrong shader type specified at line: " + std::to_string(startLine) + ", file: " + m_filePath);
					}
					else if (internalShaders.at(shaderType).m_status == SHADER_STATUS::NICHTS)
					{
						// Compile Vertex Shader

						char const * sourceCodePointer = shaderCode.c_str();

						internalShaders.at(shaderType).m_id = glCreateShader(getGLShaderEnum(shaderType));
						gl_check_error();
						glShaderSource(internalShaders.at(shaderType).m_id, 1, &sourceCodePointer, NULL);
						internalShaders.at(shaderType).m_status = SHADER_STATUS::HASCODE;
						internalShaders.at(shaderType).m_startLine = startLine;
						gl_check_error();
						if (shaderType == SHADER_COMPUTE)
							break;
					}
					shaderCode.clear();
				}
				
			}
							
			shaderStream.close();
		}
		else {
			Logger::Message(LOG_ERROR, "Impossible to open " + m_filePath + ". Are you in the right directory ? Don't forget to read the FAQ !\n");
			getchar();
			return false;
		}

		gl_check_error();

		Logger::Message(LOG_INFO, "Compiling shaders from " + m_filePath);
		//Compile Individual shaders
		for( int i=0; i < internalShaders.size(); i++ )
		{
			if ( internalShaders.at(i).m_status == SHADER_STATUS::HASCODE ) {
				GLuint shaderId = internalShaders.at(i).m_id;
				glCompileShader(shaderId);
				gl_check_error();
				// Check if compiled successfully
				glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
				if (InfoLogLength > 0) {
					std::vector<char> shaderErrorMessage(InfoLogLength + 1);
					glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &shaderErrorMessage[0]);
					//printf("%s\n", &shaderErrorMessage[0]);

					std::istringstream ErrorLog(&shaderErrorMessage[0]);
					std::string logLine;
					while (getline(ErrorLog, logLine,'\n')) {
						if (logLine.substr(0, 5) == "ERROR") {
							std::istringstream ss_logLine(logLine);
							std::string s_internalLine;
							std::getline(ss_logLine, s_internalLine, ':'); getline(ss_logLine, s_internalLine, ':'); getline(ss_logLine, s_internalLine, ':');
							int internalLine = stoi(s_internalLine);
							std::string errorWithCorrectLine = "SHADER_ERROR: "+std::to_string(internalLine + internalShaders.at(i).m_startLine) + ": " + logLine.substr(14,logLine.size());
							Logger::Message( LOG_ERROR, errorWithCorrectLine);
						}
					}
					
					if (Result == GL_FALSE) return false;
				}
				internalShaders.at(i).m_status = SHADER_STATUS::COMPILED;
			}
		}

		// Link the program
		Logger::Message(LOG_INFO, "Linking Shaders....");
		GLuint ProgramID = glCreateProgram();
		if (internalShaders.at(SHADER_COMPUTE).m_status == SHADER_STATUS::COMPILED) {
			Logger::Message(LOG_INFO, "Attaching Compute Shader.");
			glAttachShader(ProgramID, internalShaders.at(SHADER_COMPUTE).m_id);
		}
		else
		{
			if (internalShaders.at(SHADER_VERTEX).m_status == SHADER_STATUS::COMPILED) {
				Logger::Message(LOG_INFO, "Attaching Vertex Shader.");
				glAttachShader(ProgramID, internalShaders.at(SHADER_VERTEX).m_id);
				internalShaders.at(SHADER_VERTEX).m_status = LINKED;
			}
			if (internalShaders.at(SHADER_GEOMETRY).m_status == SHADER_STATUS::COMPILED) {
				Logger::Message(LOG_INFO, "Attaching Geometry Shader.");
				glAttachShader(ProgramID, internalShaders.at(SHADER_GEOMETRY).m_id);
				internalShaders.at(SHADER_GEOMETRY).m_status = LINKED;
			}
			if (internalShaders.at(SHADER_FRAGMENT).m_status == SHADER_STATUS::COMPILED) {
				Logger::Message(LOG_INFO, "Attaching Fragment Shader.");
				glAttachShader(ProgramID, internalShaders.at(SHADER_FRAGMENT).m_id);
				internalShaders.at(SHADER_FRAGMENT).m_status = LINKED;
			}
		}
		glLinkProgram(ProgramID);
		gl_check_error();

		// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		
		if (Result == GL_FALSE) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			Logger::Message(LOG_ERROR, "Error in linking. "+std::string(&ProgramErrorMessage[0], InfoLogLength + 1));
			return false;
		}
		gl_check_error();

		for (int i = 0; i < internalShaders.size(); i++) {
			if (internalShaders.at(i).m_status == LINKED) {
				glDetachShader(ProgramID, internalShaders.at(i).m_id);
				gl_check_error();
			}
			
		}

		if (m_id) 
			glDeleteProgram(m_id);
		m_id = ProgramID;
		gl_check_error();
		return true;
	}

}