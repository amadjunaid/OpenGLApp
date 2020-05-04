#include "Model.h"


namespace mview {
	Model::Model(): SceneObject()
	{
		m_type = MOBJECT_TYPE::TRIANGLE_MESH;
		m_matLib.reset(new MaterialLib());
		m_texLib.reset(new TextureLib());
	}


	Model::~Model()
	{
#ifdef _DEBUG
		Logger::Message(LOG_INFO, m_name + " deleted.");
#endif
	}

	void Model::loadFromFileOld(std::string filePath, const shrd_MaterialLib matLib)
	{
		std::string fileType = filePath.substr(filePath.size() - 3, 3);
		bool isTriangleLoaded = false;
		std::string materialFilePath = "";
		std::string materialName = "";
		shrd_TriangleMesh triMesh(new TriangleMesh());
		//Add more file types here
		if (fileType.compare("obj") == 0) {
			isTriangleLoaded = triMesh->loadObj(filePath, materialFilePath, materialName);
			if(strcmp(materialFilePath.c_str(), "") != 0)
				//m_materialID = matLib->AddMaterialFrom_MtlFile(materialFilePath, materialName);			
			if (!isTriangleLoaded) {
				Logger::Message(LOG_SEVERITY::LOG_ERROR, "Mesh load failed for file " + filePath);
				return;
			}
		}
		m_meshes.push_back(triMesh);
		Logger::Message(LOG_SEVERITY::LOG_INFO, "Mesh load successful for file " + filePath);
		m_name = getFileName(filePath);		

		m_initialized = true;
	}

	void Model::LoadFromFile(std::string filePath)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_GenNormals);

		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			Logger::Message(LOG_ERROR, "ASSIMP Error with loading mesh");
			return;
		}
		m_path = GetDirPath(filePath);

		m_name = getFileName(filePath);
		processNode(scene->mRootNode, scene);
		Logger::Message(LOG_SEVERITY::LOG_INFO, "Mesh load successful for file " + filePath);
		

		m_initialized = true;

	}

	const shrd_MaterialLib Model::GetMatLib()
	{
		return m_matLib;
	}

	const shrd_TextureLib Model::GetTexLib()
	{
		return m_texLib;
	}

	TEXTURE_TYPE Model::GetOwnTextureType(aiTextureType assimpTexType)
	{
		switch (assimpTexType) {
		case (aiTextureType_DIFFUSE):
			return TEXTURE_TYPE::TT_DIFFUSE;
			break;
		case (aiTextureType_SPECULAR):
			return TEXTURE_TYPE::TT_SPECULAR;
			break;
		default:
			return TEXTURE_TYPE(-1);
		}
	}

	aiTextureType Model::GetAssimpTextureType(TEXTURE_TYPE texType)
	{
		switch (texType) {
		case (TT_DIFFUSE):
			return aiTextureType_DIFFUSE;
			break;
		case (TT_SPECULAR):
			return aiTextureType_SPECULAR;
			break;
		default:
			return aiTextureType(-1);
		}
	}	

	void Model::processNode(aiNode* node, const aiScene* scene)
	{
		// Process all the node's meshes (if any)
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			shrd_TriangleMesh triMesh = shrd_TriangleMesh(new TriangleMesh(mesh, scene));
			this->m_meshes.push_back(triMesh);

			// Process material
			if (mesh->mMaterialIndex >= 0)
			{
				shrd_Material mat(new Material());
				mat->name = m_name + "_material";
				aiMaterial* ai_material = scene->mMaterials[mesh->mMaterialIndex];
				aiString matName;
				if (AI_SUCCESS == ai_material->Get(AI_MATKEY_NAME, matName)) {
					mat->name = std::string(matName.C_Str());
				}

				float c[] = { 1.f, 1.f, 1.f, 1.f };
				aiColor4D matProperty;
				float shininess; unsigned int max;
				if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_AMBIENT, &matProperty))
					mat->ambient = glm::vec4(matProperty.r, matProperty.g, matProperty.b, matProperty.a);
				if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_DIFFUSE, &matProperty))
					mat->diffuse = glm::vec4(matProperty.r, matProperty.g, matProperty.b, matProperty.a);
				if (AI_SUCCESS == aiGetMaterialColor(ai_material, AI_MATKEY_COLOR_SPECULAR, &matProperty)) {
					mat->specular = glm::vec4(matProperty.r, matProperty.g, matProperty.b, matProperty.a);
					if (AI_SUCCESS == aiGetMaterialFloatArray(ai_material, AI_MATKEY_SHININESS, &shininess, &max))
						mat->shininess = shininess/4.f; //Dividing by 4 as assimp pre-multiplies by 4 for unknown reasons(ObjFileImporter.cpp: 607)

				}
				triMesh->m_materialID = m_matLib->AddMaterials(mat);
								
				for (size_t i = 0; i < TEXTURE_TYPE::TT_COUNT; i++) {
					for (size_t i = 0; i < ai_material->GetTextureCount(GetAssimpTextureType(TEXTURE_TYPE(i))); i++)
					{
						aiString texFile;
						if (AI_SUCCESS == ai_material->GetTexture(GetAssimpTextureType(TEXTURE_TYPE(i)), (int)i, &texFile))
							triMesh->m_textureIDs[i] = m_texLib->AddTexture(TEXTURE_TYPE(i), std::string(texFile.C_Str()), m_path);
					}					
				}

			}
		}
		// Then do the same for each of its children
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			this->processNode(node->mChildren[i], scene);
		}
	}	
	
}
