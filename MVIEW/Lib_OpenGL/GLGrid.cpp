#include "GLGrid.h"
#include <stdlib.h>

namespace mview {

	GLGrid::GLGrid()
	{
		attributeBuffers = std::vector<VertexAttributeBuffer>(VERTEX_ATTRIBUTES::VA_COUNT, VertexAttributeBuffer(0, 0, -1));
	}


	void GLGrid::Init()
	{
		//glGenVertexArrays(1, &VertexArrayID);
		//glBindVertexArray(VertexArrayID);		
		

		std::vector<GLfloat> positionsData;
		std::vector<GLfloat> colorData;
		float point_pos = 0.f - (float)m_numLines / 2.f * m_spacing;
		float endPoints = point_pos;

		for (int i = 0; i <= m_numLines; i++) {
			if (point_pos == 0.f) {
				colorData.push_back(0.f); colorData.push_back(0.471f); colorData.push_back(0.882f);
				colorData.push_back(0.2f); colorData.push_back(0.2f); colorData.push_back(0.8f);
			}
			else { 
				colorData.push_back(0.25f); colorData.push_back(0.25f); colorData.push_back(0.25f);
				colorData.push_back(0.25f); colorData.push_back(0.25f); colorData.push_back(0.25f);
			}

			positionsData.push_back(point_pos); positionsData.push_back(0); positionsData.push_back(-endPoints);
			positionsData.push_back(point_pos); positionsData.push_back(0); positionsData.push_back(endPoints);

			if (point_pos == 0.f)	{
				colorData.push_back(0.8f); colorData.push_back(0.2f); colorData.push_back(0.2f);
				colorData.push_back(0.8f); colorData.push_back(0.2f); colorData.push_back(0.2f);				
			}
			else {
				colorData.push_back(0.25f); colorData.push_back(0.25f); colorData.push_back(0.25f);
				colorData.push_back(0.25f); colorData.push_back(0.25f); colorData.push_back(0.25f);
			}

			positionsData.push_back(-endPoints); positionsData.push_back(0); positionsData.push_back(point_pos);
			positionsData.push_back(endPoints); positionsData.push_back(0); positionsData.push_back(point_pos);

			point_pos += m_spacing;
		}

		if (attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id)
			glDeleteBuffers(1, &(attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id));
		glGenBuffers(1, &(attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id));
		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*positionsData.size(), positionsData.data(), GL_STATIC_DRAW);

		gl_check_error();		
		attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_type = GL_FLOAT;

		if (attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id)
			glDeleteBuffers(1, &(attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id));
		glGenBuffers(1, &(attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id));
		glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colorData.size(), colorData.data(), GL_STATIC_DRAW);

		gl_check_error();
		attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_type = GL_FLOAT;

		std::string shaderFile = std::string(getenv("GLSHADERS_PATH"));
		shaderFile += "GridShader.glsl";
		m_shader.reset(new GLShaderTechnique(shaderFile.c_str()));
		gl_check_error();
		//glBindVertexArray(0);
	}

	void GLGrid::Draw(const longInt& frameNumber, const glm::mat4& viewProj)
	{
		//glBindVertexArray(VertexArrayID);
		glUseProgram(m_shader->m_id);
		gl_check_error();

		GLuint mvpID = glGetUniformLocation(m_shader->m_id, "viewProj");
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &viewProj[0][0]);
		gl_check_error();

		//Configure attribute buffers
		for (int i = 0; i < attributeBuffers.size(); i++) {
			if (attributeBuffers.at(i).m_id) {
				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(i);
				glBindBuffer(GL_ARRAY_BUFFER, attributeBuffers.at(i).m_id);
				glVertexAttribPointer(
					i,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					VertexAttribute::ElementsPerVertex(i),                   // size per element e.g. 3 for a 3 vector
					attributeBuffers.at(i).m_type,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);
			}
			gl_check_error();
		}

		glDrawArrays(GL_LINES, 0, (m_numLines+1)*2*2);
		gl_check_error();

		glDisableVertexAttribArray(0);
		glUseProgram(0);
		//glBindVertexArray(0);
	}


	GLGrid::~GLGrid()
	{
		for (int i = 0; i < attributeBuffers.size(); i++)
		{
			if (attributeBuffers.at(i).m_id) glDeleteBuffers(1, &(attributeBuffers.at(i).m_id));
		}
		
		//glDeleteVertexArrays(1, &VertexArrayID);
	}
	
}
