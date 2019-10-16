
#ifndef GLGRID_H
#define GLGRID_H

#include "CommonUtils_Lib_OpenGL.h"
#include "GLTriangleMesh.h"
#include "GLShader.h"
#include "GLError.h"

namespace mview {

	class DLLEXPORT GLGrid
	{
	private:

		std::vector<VertexAttributeBuffer> attributeBuffers;
		int m_numLines = 10;
		float m_spacing = 0.5f;
		shrd_GLShaderTechnique m_shader;
		GLuint VertexArrayID;
	public:
		
		GLGrid();

		

		~GLGrid();

		void Init();
		void Draw(const longInt& frameTime, const glm::mat4& viewProj);

	};

	typedef std::shared_ptr<GLGrid> shrd_GLGrid;
}

#endif // !GLGRID_H

