#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace mview
{
	TextureLib::TextureLib()
	{
		m_textures.push_back(shrd_Texture(new Texture()));
	}

	int TextureLib::AddTexture(const shrd_Texture tex)
	{
		m_textures.push_back(tex);
		return m_textures.size() - 1;
	}

	int TextureLib::AddTexture(TEXTURE_TYPE type, std::string filePath, std::string modelPath)
	{
		shrd_Texture tex = shrd_Texture(new Texture());
		tex->m_data = stbi_load(filePath.c_str(), &tex->m_width, &tex->m_height, &tex->m_channels, 3);
		
		if (!tex->m_data) {
			std::string absolutePath = modelPath + filePath;
			tex->m_data = stbi_load(absolutePath.c_str(), &tex->m_width, &tex->m_height, &tex->m_channels, 3);
		}
		tex->m_type = type;
		tex->m_path = filePath;
		m_textures.push_back(tex);
		return m_textures.size() - 1;
	}

	void TextureLib::DeleteTexture(int idx)
	{
		m_textures.erase(m_textures.begin() + idx);
	}

	const shrd_Texture TextureLib::GetTex(int idx)
	{
		if (idx<m_textures.size())
			return m_textures.at(idx);
		else
			return nullptr;
	}

	TextureLib::~TextureLib()
	{		
	}

}