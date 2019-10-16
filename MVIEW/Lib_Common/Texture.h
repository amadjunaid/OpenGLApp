#pragma once
#ifndef TEXTURES_H
#define TEXTURES_H


#include "CommonUtils.h"



namespace mview

{
	/*IMPORTANT*/
	/*1. When adding new type.. add the corresponding type in renderer's texture's name returning function and shaders(GL).*/
	enum TEXTURE_TYPE {TT_DIFFUSE, TT_SPECULAR, TT_COUNT};
	struct Texture
	{
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;	
		uchar* m_data = nullptr;
		std::string m_path = "";
		TEXTURE_TYPE m_type;
		Texture() {};
		~Texture() { if (m_data) delete m_data; }


	};
	typedef std::shared_ptr<Texture> shrd_Texture;

	class DLLEXPORT TextureLib
	{
	protected:
		std::vector<shrd_Texture> m_textures;
	public:
		TextureLib();
		int AddTexture(const shrd_Texture tex);
		int AddTexture(TEXTURE_TYPE type, std::string filePath, std::string modelPath);
		void DeleteTexture(int idx);
		const shrd_Texture GetTex(int idx);
		~TextureLib();
	};

	typedef std::shared_ptr<TextureLib> shrd_TextureLib;
}

#endif // !TEXTURES_H

