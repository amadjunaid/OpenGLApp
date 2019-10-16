#pragma once
#ifndef GLTERRAIN_H
#define GLTERRAIN_H

#include "CommonUtils_Lib_OpenGL.h"
#include "GLObject.h"
#include "GLShader.h"
#include "GLError.h"


#include <Zone.h>

namespace mview
{
	class DLLEXPORT GLTerrain: public GLObject
	{
	private:
		std::vector<VertexAttributeBuffer> m_attributeBuffers;

		shrd_GLShaderTechnique m_shader;
		GLuint m_vertexArrayID;
		shrd_Terrain m_terrain;

	public:
		shrd_mat4 modelTransform;
		GLTerrain(shrd_Terrain terrain, longInt globalId, shrd_mat4 modelTransform);
		~GLTerrain();

		void Draw(const longInt& frameTime, const glm::mat4& viewProj);
		void UpdateParam(int name);
	};

	typedef std::shared_ptr<GLTerrain> shrd_GLTerrain;
	typedef std::vector<shrd_GLTerrain> GLTerrainList;
	typedef std::shared_ptr<GLTerrainList> shrd_GLTerrainList;

	typedef SpecialCompare<shrd_GLTerrain> CompareGLTerrain;
}
#endif // !GLTERRAIN_H


