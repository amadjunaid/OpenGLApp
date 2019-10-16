#include "GLTerrain.h"


namespace mview
{

	GLTerrain::GLTerrain(shrd_Terrain terrain, longInt globalId, shrd_mat4 modelTransform): GLObject(globalId)
	{

		m_terrain = terrain;
		modelTransform = modelTransform;

		
		m_attributeBuffers = std::vector<VertexAttributeBuffer>(VERTEX_ATTRIBUTES::VA_COUNT, VertexAttributeBuffer(0, 0, -1));

		auto& positionData = m_terrain->m_vertices[VA_POSITION].unstructuredData;
		auto& colorData = m_terrain->m_vertices[VA_COLOR].unstructuredData;
		if (m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id)
			glDeleteBuffers(1, &(m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id));
		glGenBuffers(1, &(m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id));
		glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*positionData.size(), positionData.data(), GL_STATIC_DRAW);

		gl_check_error();
		m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_POSITION).m_type = GL_FLOAT;

		if (m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id)
			glDeleteBuffers(1, &(m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id));
		glGenBuffers(1, &(m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id));
		glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colorData.size(), colorData.data(), GL_STATIC_DRAW);

		gl_check_error();
		m_attributeBuffers.at(VERTEX_ATTRIBUTES::VA_COLOR).m_type = GL_FLOAT;

		std::string shaderFile = std::string(getenv("GLSHADERS_PATH"));
		shaderFile += "GridShader.glsl";
		m_shader.reset(new GLShaderTechnique(shaderFile.c_str()));
		gl_check_error();
	}


	GLTerrain::~GLTerrain()
	{
		for (int i = 0; i < m_attributeBuffers.size(); i++)
		{
			if (m_attributeBuffers.at(i).m_id) glDeleteBuffers(1, &(m_attributeBuffers.at(i).m_id));
		}
#ifdef _DEBUG
		Logger::Message(LOG_INFO, "Renderer data (Vertex data for " + m_terrain->m_objectName + ") deleted.");
#endif
	}

	void GLTerrain::Draw(const longInt & frameTime, const glm::mat4 & viewProj)
	{
		//glBindVertexArray(VertexArrayID);
		glUseProgram(m_shader->m_id);
		gl_check_error();

		GLuint mvpID = glGetUniformLocation(m_shader->m_id, "viewProj");
		glUniformMatrix4fv(mvpID, 1, GL_FALSE, &viewProj[0][0]);
		gl_check_error();

		//Configure attribute buffers
		for (int i = 0; i < m_attributeBuffers.size(); i++) {
			if (m_attributeBuffers.at(i).m_id) {
				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(i);
				glBindBuffer(GL_ARRAY_BUFFER, m_attributeBuffers.at(i).m_id);
				glVertexAttribPointer(
					i,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					VertexAttribute::ElementsPerVertex(i),                   // size per element e.g. 3 for a 3 vector
					m_attributeBuffers.at(i).m_type,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);
			}
			gl_check_error();
		}

		glDrawArrays(GL_LINES, 0, (m_terrain->m_numLines + 1) * 2 * 2);
		gl_check_error();

		glDisableVertexAttribArray(0);
		glUseProgram(0);
		//glBindVertexArray(0);
	}

	void GLTerrain::UpdateParam(int name)
	{
	}	
}