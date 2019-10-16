#include "GLUBOResource.h"



namespace mview
{
	GLuint GLUBOResource::m_countBPI = UBOInfoData_BPI+1; //Zero is reserved for the UBO Info struct

	void GLUBOResource::BindToShader(shrd_GLShaderTechnique shader, const int & index)
	{
		std::string IndexedName = m_UBONameInShader + "[" + std::to_string(index) + "]";
		unsigned int blockIndex = glGetUniformBlockIndex(shader->m_id, IndexedName.c_str());
		glBindBufferBase(GL_UNIFORM_BUFFER, m_bpi, m_ubo);
		glUniformBlockBinding(shader->m_id, blockIndex, m_bpi);
		gl_check_error();
		m_isBound = true;
	}

	void GLUBOResource::BindToShaderNonIndexed(shrd_GLShaderTechnique shader)
	{
		unsigned int blockIndex = glGetUniformBlockIndex(shader->m_id, m_UBONameInShader.c_str());
		glBindBufferBase(GL_UNIFORM_BUFFER, m_bpi, m_ubo);
		glUniformBlockBinding(shader->m_id, blockIndex, m_bpi);
		gl_check_error();
		m_isBound = true;
	}

	bool GLUBOResource::CheckIfBound()
	{
		if (!m_isBound) {
			Logger::Message(LOG_SEVERITY::LOG_WARNING, "Resource " + m_UBONameInShader + " not bound in shader.");
			return false;
		}
		return true;
	}

	GLUBOResource::GLUBOResource()
	{
		m_bpi = m_countBPI++;
		glGenBuffers(1, &m_ubo);
	}


	GLUBOResource::~GLUBOResource()
	{
		if(m_ubo)
			glDeleteBuffers(1, &m_ubo);
#ifdef _DEBUG
		Logger::Message(LOG_INFO, "Renderer data(Shader Resource) '" + m_UBONameInShader + "' deleted.");
#endif
	}

}