#include "TriangleMesh.h"
#include "Texture.h"
#include <regex>

namespace mview {

	/*TriangleMesh::TriangleMesh()
	{		
		

	}*/

	TriangleMesh::TriangleMesh()
	{
		m_vertices = std::vector<VertexAttribute>(VERTEX_ATTRIBUTES::VA_COUNT);
		m_vertexIndices = std::vector<VertexAttributeIndex>(VERTEX_ATTRIBUTES::VA_COUNT);	
		m_textureIDs = std::vector<int>(TEXTURE_TYPE::TT_COUNT, 0);
	}

	TriangleMesh::TriangleMesh(aiMesh * mesh, const aiScene * scene): TriangleMesh()
	{
		std::vector< float > temp_positions;
		std::vector< float > temp_uvs;
		std::vector< float > temp_normals;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			temp_positions.push_back(mesh->mVertices[i].x); temp_positions.push_back(mesh->mVertices[i].y); temp_positions.push_back(mesh->mVertices[i].z);
			if(mesh->mNormals)
				temp_normals.push_back(mesh->mNormals[i].x); temp_normals.push_back(mesh->mNormals[i].y); temp_normals.push_back(mesh->mNormals[i].z);
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				temp_uvs.push_back(mesh->mTextureCoords[0][i].x); temp_uvs.push_back(mesh->mTextureCoords[0][i].y);				
			}
		}
		m_numVertices = mesh->mNumVertices;
		m_numTris = mesh->mNumFaces;

		// Process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for(size_t j = 0; j < face.mNumIndices; j++) {
				int index = face.mIndices[j];
				unsigned int posIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_POSITION)*index;
				m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex));
				m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex + 1));
				m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex + 2));

				if (!temp_uvs.empty()) {
					unsigned int uvIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_UV) * index;
					m_vertices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(temp_uvs.at(uvIndex));
					m_vertices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(temp_uvs.at(uvIndex + 1));
				}

				if (!temp_normals.empty()) {
					unsigned int normalIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_NORMAL) * index;
					m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex));
					m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex + 1));
					m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex + 2));
				}
			}

		}
		
		m_objectName = std::string(mesh->mName.C_Str());

			
	}	

	TriangleMesh::~TriangleMesh()
	{
	}	

	void TriangleMesh::loadData(int type, VertexAttribute& data)
	{
		m_vertices[type] = data;
	}

	void TriangleMesh::loadData(int type, const float data[])
	{
		m_vertices[type] = VertexAttribute((int)m_numVertices * VertexAttribute::ElementsPerVertex(type), data);
	}

	enum OBJTriangleFormat {V_VT_VN, V_VT_, V__VN, V__} objTriangleFormat;

	bool TriangleMesh::loadObj(std::string filePath, std::string& materialFilePath, std::string& materialName)
	{
		
		FILE * file = fopen(filePath.c_str(), "r");

		//check if file is opened and can be loaded
		if (file == NULL) {
			Logger::Message(LOG_SEVERITY::LOG_ERROR, "Impossible to open model file: " + filePath);
			return false;
		}

		std::vector< float > temp_positions;
		std::vector< float > temp_uvs;
		std::vector< float > temp_normals;
		std::string triangleFormatString;

		//Determine triangle data format first before reading
		while (1) {
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				Logger::Message(LOG_SEVERITY::LOG_ERROR, "No triangle found in mesh file: " + filePath);
				return false; // EOF = End Of File. Quit the loop.
			}
				
			if (strcmp(lineHeader, "f") == 0) {
				char tempData[128];
				int matches = fscanf(file, "%s", tempData);
				if (matches == 1) {
					std::regex V_VT_VN("[0-9]+\/[0-9]+\/[0-9]+\0");
					std::regex V_VT_("[0-9]+\/[0-9]+\/\0");
					std::regex V__VN("[0-9]+\/\/[0-9]+\0");
					std::regex V__("[0-9]+\/\/\0");
					//std::string str_tempData(tempData);
					if (std::regex_match(tempData, V_VT_VN)) {
						triangleFormatString = "%d/%d/%d %d/%d/%d %d/%d/%d\n";
						objTriangleFormat = OBJTriangleFormat::V_VT_VN;
						break;
					}
					else if (std::regex_match(tempData, V_VT_)) {
						triangleFormatString = "%d/%d/ %d/%d/ %d/%d/\n";
						objTriangleFormat = OBJTriangleFormat::V_VT_;
						break;
					}
					else if (std::regex_match(tempData, V__VN)) {
						triangleFormatString = "%d//%d %d//%d %d//%d\n";
						objTriangleFormat = OBJTriangleFormat::V__VN;
						break;
					}
					else if (std::regex_match(tempData, V__)) {
						triangleFormatString = "%d// %d// %d//\n";
						objTriangleFormat = OBJTriangleFormat::V__;
						break;
					}
					else
					{
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "Unknown triangle format in mesh file: " + filePath);
						return false;
					}


				}
				else {
					Logger::Message(LOG_SEVERITY::LOG_ERROR, "Unknown triangle format in mesh file: " + filePath);
					return false;
				}

			}

		}

		rewind(file);
		//Start reading line by line
		while (1) {
			//Temp holders for indexed data
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

			// else : parse lineHeader
			if (strcmp(lineHeader, "v") == 0) {
				float x,y,z;
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				temp_positions.push_back(x);
				temp_positions.push_back(y);
				temp_positions.push_back(z);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				float x,y;
				fscanf(file, "%f %f\n", &x, &y);
				temp_uvs.push_back(x);
				temp_uvs.push_back(y);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				float x, y, z;
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				temp_normals.push_back(x);
				temp_normals.push_back(y);
				temp_normals.push_back(z);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				//Switching based on triangle strucutre to read correctly
				int matches = 0;
				switch (objTriangleFormat)
				{
				case OBJTriangleFormat::V_VT_VN:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					if (matches != 9) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[2]);
					break;
				case OBJTriangleFormat::V_VT_:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
					if (matches != 6) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[2]);
					break;
				case OBJTriangleFormat::V__VN:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
					if (matches != 6) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[2]);
					break;
				case OBJTriangleFormat::V__:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
					if (matches != 6) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					break;
				default:
					break;
				}
				
			}
			else if (strcmp(lineHeader, "mtllib") == 0)
			{
				char fileName[128];
				int matches = fscanf(file, "%s", fileName);
				if (matches != 1)
				{
					Logger::Message(LOG_SEVERITY::LOG_ERROR, "Material name error in model file " + filePath);
				}
				else

				materialFilePath = std::string(GetDirPath(filePath) + fileName);
			}
			else if (strcmp(lineHeader, "usemtl") == 0)
			{
				char materialName_char[128];
				int matches = fscanf(file, "%s", materialName_char);
				materialName = std::string(materialName_char);
			}
		
		
		}

		m_numVertices = m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.size() * 3;
		m_numTris = m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.size();
		
		//Indexing the triangles to have non-indexed data in local vertex buffers
		for (unsigned int i = 0; i < m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.size(); i++) {
			unsigned int posIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_POSITION)*(m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.at(i)-1);
			m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex));
			m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex+1));
			m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex+2));
			
			if (!m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.empty()) {
				unsigned int uvIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_UV) * (m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.at(i) - 1);
				m_vertices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(temp_uvs.at(uvIndex));
				m_vertices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(temp_uvs.at(uvIndex + 1));
			}

			if(!m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.empty()) {
				unsigned int normalIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_NORMAL) * (m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.at(i) - 1);
				m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex));
				m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex + 1));
				m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex + 2));
			}
			
		}
		
		m_objectName = getFileName(filePath);
		return true;
	}

	bool TriangleMesh::loadObjWithoutMaterial(std::string filePath)
	{
		FILE * file = fopen(filePath.c_str(), "r");

		//check if file is opened and can be loaded
		if (file == NULL) {
			Logger::Message(LOG_SEVERITY::LOG_ERROR, "Impossible to open the file: " + filePath);
			return false;
		}

		std::vector< float > temp_positions;
		std::vector< float > temp_uvs;
		std::vector< float > temp_normals;
		std::string triangleFormatString;

		//Determine triangle data format first before reading
		while (1) {
			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				Logger::Message(LOG_SEVERITY::LOG_ERROR, "No triangle found in mesh file: " + filePath);
				return false; // EOF = End Of File. Quit the loop.
			}

			if (strcmp(lineHeader, "f") == 0) {
				char tempData[128];
				int matches = fscanf(file, "%s", tempData);
				if (matches == 1) {
					std::regex V_VT_VN("[0-9]+\/[0-9]+\/[0-9]+\0");
					std::regex V_VT_("[0-9]+\/[0-9]+\/\0");
					std::regex V__VN("[0-9]+\/\/[0-9]+\0");
					std::regex V__("[0-9]+\/\/\0");
					//std::string str_tempData(tempData);
					if (std::regex_match(tempData, V_VT_VN)) {
						triangleFormatString = "%d/%d/%d %d/%d/%d %d/%d/%d\n";
						objTriangleFormat = OBJTriangleFormat::V_VT_VN;
						break;
					}
					else if (std::regex_match(tempData, V_VT_)) {
						triangleFormatString = "%d/%d/ %d/%d/ %d/%d/\n";
						objTriangleFormat = OBJTriangleFormat::V_VT_;
						break;
					}
					else if (std::regex_match(tempData, V__VN)) {
						triangleFormatString = "%d//%d %d//%d %d//%d\n";
						objTriangleFormat = OBJTriangleFormat::V__VN;
						break;
					}
					else if (std::regex_match(tempData, V__)) {
						triangleFormatString = "%d// %d// %d//\n";
						objTriangleFormat = OBJTriangleFormat::V__;
						break;
					}
					else
					{
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "Unknown triangle format in mesh file: " + filePath);
						return false;
					}


				}
				else {
					Logger::Message(LOG_SEVERITY::LOG_ERROR, "Unknown triangle format in mesh file: " + filePath);
					return false;
				}

			}

		}

		rewind(file);
		//Start reading line by line
		while (1) {
			//Temp holders for indexed data
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

					   // else : parse lineHeader
			if (strcmp(lineHeader, "v") == 0) {
				float x, y, z;
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				temp_positions.push_back(x);
				temp_positions.push_back(y);
				temp_positions.push_back(z);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				float x, y;
				fscanf(file, "%f %f\n", &x, &y);
				temp_uvs.push_back(x);
				temp_uvs.push_back(y);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				float x, y, z;
				fscanf(file, "%f %f %f\n", &x, &y, &z);
				temp_normals.push_back(x);
				temp_normals.push_back(y);
				temp_normals.push_back(z);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				//Switching based on triangle strucutre to read correctly
				int matches = 0;
				switch (objTriangleFormat)
				{
				case OBJTriangleFormat::V_VT_VN:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					if (matches != 9) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[2]);
					break;
				case OBJTriangleFormat::V_VT_:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
					if (matches != 6) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(uvIndex[2]);
					break;
				case OBJTriangleFormat::V__VN:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
					if (matches != 6) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(normalIndex[2]);
					break;
				case OBJTriangleFormat::V__:
					matches = fscanf(file, triangleFormatString.c_str(), &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
					if (matches != 6) {
						Logger::Message(LOG_SEVERITY::LOG_ERROR, "File can't be read by our simple parser : ( Try exporting with other options");
						return false;
					}
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[0]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[1]);
					m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(vertexIndex[2]);
					break;
				default:
					break;
				}

			}

		}

		m_numVertices = m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.size() * 3;
		m_numTris = m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.size();

		//Indexing the triangles to have non-indexed data in local vertex buffers
		for (unsigned int i = 0; i < m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.size(); i++) {
			unsigned int posIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_POSITION)*(m_vertexIndices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.at(i) - 1);
			m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex));
			m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex + 1));
			m_vertices[VERTEX_ATTRIBUTES::VA_POSITION].unstructuredData.push_back(temp_positions.at(posIndex + 2));

			if (!m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.empty()) {
				unsigned int uvIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_UV) * (m_vertexIndices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.at(i) - 1);
				m_vertices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(temp_uvs.at(uvIndex));
				m_vertices[VERTEX_ATTRIBUTES::VA_UV].unstructuredData.push_back(temp_uvs.at(uvIndex + 1));
			}

			if (!m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.empty()) {
				unsigned int normalIndex = VertexAttribute::ElementsPerVertex(VERTEX_ATTRIBUTES::VA_NORMAL) * (m_vertexIndices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.at(i) - 1);
				m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex));
				m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex + 1));
				m_vertices[VERTEX_ATTRIBUTES::VA_NORMAL].unstructuredData.push_back(temp_normals.at(normalIndex + 2));
			}

		}

		m_objectName = getFileName(filePath);
		return true;
	}
	
}
