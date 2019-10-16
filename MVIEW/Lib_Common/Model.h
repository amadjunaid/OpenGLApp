
#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "SceneObject.h"
#include "TriangleMesh.h"
#include "MaterialLib.h"
#include "Texture.h"

namespace mview {

	//************
	//Represents a tiangle mesh present in the scene
	//************
	class DLLEXPORT Model : public SceneObject
	{
	protected:
		void processNode(aiNode* node, const aiScene* scene);
		shrd_MaterialLib m_matLib;
		shrd_TextureLib m_texLib;
		std::string m_path;		
	public:
		Model();
		~Model();	
		void loadFromFileOld(std::string filePath, const shrd_MaterialLib matLib);
		void LoadFromFile(std::string filePath);
		const shrd_MaterialLib GetMatLib();
		const shrd_TextureLib GetTexLib();

		static TEXTURE_TYPE GetOwnTextureType(aiTextureType assimpTexType);
		static aiTextureType  GetAssimpTextureType(TEXTURE_TYPE texType);
	};

	typedef std::shared_ptr<Model> shrd_Model;
	typedef std::vector<shrd_Model> ModelList;
	typedef std::shared_ptr<ModelList> shrd_ModelList;
}

#endif // !RENDERABLEOBJECTS_H



