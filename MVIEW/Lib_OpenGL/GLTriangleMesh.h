
#ifndef GLTRIANGLEMESH_H
#define GLTRIANGLEMESH_H

#include "CommonUtils_Lib_OpenGL.h"
#include "GLError.h"
#include "GLTexture.h"
#include "GLObject.h"
#include "GLShader.h"
#include <TriangleMesh.h>


namespace mview {

	//TODO: Use Vertex Attribute Arrays to better handle vertex attributes.. will not need to bind everything again...
	
	

	class DLLEXPORT GLTriangleMesh: public GLObject
	{
	private:
		
		std::vector<VertexAttributeBuffer> attributeBuffers;

		GLuint colorbuffer;
		
	public:
		shrd_TriangleMesh m_triMesh;
		shrd_Param_T<RENDER_MODE> m_renderMode;
		//shrd_SceneObject m_sceneObject;
		shrd_mat4 m_modelTransform;	
		int m_materialndex = 0;
		GLTexturesList m_textures;
		//GLTriangleMesh();
		GLTriangleMesh(shrd_TriangleMesh triMesh, longInt globalId, shrd_mat4 modelTrasform);		

		~GLTriangleMesh();

		void resetData(VERTEX_ATTRIBUTES attributeType, const GLfloat* data, int size, int type);
		void UpdateParam(int name);

		void Draw(const longInt& frameNumber, const shrd_GLShaderTechnique shader);

	};
	typedef std::shared_ptr<GLTriangleMesh> shrd_GLTriangleMesh;
	typedef std::vector<shrd_GLTriangleMesh> GLTriangleMeshList;
	typedef std::shared_ptr<GLTriangleMeshList> shrd_GLTriangleMeshList;

	typedef SpecialCompare<shrd_GLTriangleMesh> CompareGLTrianlgeMesh;	
}

#endif //GLTRIANGLEMESH_H