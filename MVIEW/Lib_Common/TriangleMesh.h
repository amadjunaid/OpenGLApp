#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H

#include "CommonUtils.h"
#include "VertexAttributes.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "MaterialLib.h"

namespace mview {
	
	class DLLEXPORT TriangleMesh
	{
	
	public:

		size_t m_numVertices = 0;
		size_t m_numTris = 0;
		size_t m_materialID = 0;
		std::vector<int> m_textureIDs;
		std::string m_objectName;
		std::vector<VertexAttribute> m_vertices;
		bool m_isIndexed = false;
		std::vector<VertexAttributeIndex> m_vertexIndices;
		
		//TriangleMesh();
		TriangleMesh();

		TriangleMesh(aiMesh* mesh, const aiScene* scene);
			
		~TriangleMesh();

		void loadData(int type, VertexAttribute& data);
		void loadData(int type, const float data[]);
		bool loadObj(std::string filePath, std::string& materialFilePath, std::string& materialName);
		bool loadObjWithoutMaterial(std::string filePath);
	};

	typedef std::shared_ptr<TriangleMesh> shrd_TriangleMesh;
}

#endif // !TRIANGLEMESH_H



