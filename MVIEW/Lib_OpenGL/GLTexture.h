
#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "CommonUtils_Lib_OpenGL.h"
#include <Texture.h>
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

namespace mview {
	class DLLEXPORT GLTexture
	{

	public:
		int g_texID = 0;
		shrd_TextureLib g_texLib = nullptr;
		GLuint m_GLId = 0;
		GLTexture();
		GLTexture(int texID, const shrd_TextureLib);
		static std::string GetTexNameinShader(TEXTURE_TYPE type);
		~GLTexture();

		bool loadBMP(const std::string& imagepath);
		bool loadDDS(const std::string & imagepath);
	};


	typedef std::shared_ptr<GLTexture> shrd_GLTexture;
	typedef std::vector<shrd_GLTexture> GLTexturesList;
}
#endif // !GLTEXTURE_H