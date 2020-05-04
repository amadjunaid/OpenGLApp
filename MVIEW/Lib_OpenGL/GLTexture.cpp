#include "GLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "GLError.h"

namespace mview {
	GLTexture::GLTexture()
	{
		
	}

	GLTexture::GLTexture(int texID, const shrd_TextureLib texLib)
	{
		g_texID = texID;
		g_texLib = texLib;
		shrd_Texture tex = texLib->GetTex(g_texID);
		if (tex->m_data)
		{
			//Creating a GL texture for the data
			glGenTextures(1, &m_GLId);
			
			glBindTexture(GL_TEXTURE_2D, m_GLId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex->m_width, tex->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->m_data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);

			
			glBindTexture(GL_TEXTURE_2D, 0);

			gl_check_error();
		}
	}

	std::string GLTexture::GetTexNameinShader(TEXTURE_TYPE type)
	{
		switch (type)
		{
		case TEXTURE_TYPE::TT_DIFFUSE:
			return "texture_Diffuse";
		case TEXTURE_TYPE::TT_SPECULAR:
			return "texture_Specular";
		default:
			return "";
		}
		
	}


	GLTexture::~GLTexture()
	{
		if (m_GLId)
			glDeleteTextures(1, &m_GLId);
	}

	bool GLTexture::loadBMP(const std::string& imagepath)
	{
		// Data read from the header of the BMP file
		//unsigned char header[54]; // Each BMP file begins by a 54-bytes header		
		//unsigned int dataPos; // Position in the file where the actual data begins
		//unsigned int imageSize; // = width*height*3

		//FILE * file = fopen(imagepath.c_str(), "rb");
		//if (!file) { Logger::Message(LOG_ERROR, "Cannot open texture file: " + imagepath); return false; }

		//if (fread(header, 1, 54, file) != 54) {
		//	Logger::Message(LOG_ERROR, "Provided file: " + imagepath + " is not a correct BMP file");
		//	return false;
		//}

		//if (header[0] != 'B' || header[1] != 'M') {
		//	Logger::Message(LOG_ERROR, "Provided file: " + imagepath + " is not a correct BMP file");
		//	return false;
		//}

		////Get info from the header
		//dataPos = *(int*)&(header[0x0A]);
		//imageSize = *(int*)&(header[0x22]);
		//m_width = *(int*)&(header[0x12]);
		//m_height = *(int*)&(header[0x16]);

		//// Some BMP files are misformatted, guess missing information
		//if (imageSize == 0)    imageSize = m_width * m_height * 3; // 3 : one byte for each Red, Green and Blue component
		//if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

											 // Create a buffer
		//m_data.reset( new uchar[imageSize]);

		// Read the actual data from the file into the buffer
		//fread(m_data.get(), 1, imageSize, file);

		////Everything is in memory now, the file can be closed
		//fclose(file);
		int m_width, m_height, m_channels;
		uchar* data = stbi_load(imagepath.c_str(), &m_width, &m_height, &m_channels, 3);
		if (data)
		{
			//Creating a GL texture for the data
			glGenTextures(1, &m_GLId);
			
			glBindTexture(GL_TEXTURE_2D, m_GLId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}
		
		return true;


	}

	bool GLTexture::loadDDS(const std::string & imagepath)
	{
		unsigned char header[124];

		FILE *fp;

		/* try to open the file */
		fp = fopen(imagepath.c_str(), "rb");
		if (fp == NULL) {
			Logger::Message(LOG_ERROR," Cannot open texture file: " + imagepath);
			return false;
		}

		/* verify the type of file */
		char filecode[4];
		fread(filecode, 1, 4, fp);
		if (strncmp(filecode, "DDS ", 4) != 0) {
			fclose(fp);
			Logger::Message(LOG_ERROR, " Texture file: " + imagepath + " not a valid DDS file.");
			return false;
		}

		/* get the surface desc */
		fread(&header, 124, 1, fp);
		int m_width, m_height;
		m_height = *(unsigned int*)&(header[8]);
		m_width = *(unsigned int*)&(header[12]);
		unsigned int linearSize = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC = *(unsigned int*)&(header[80]);

		unsigned int bufsize;
		/* how big is it going to be including all mipmaps? */
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		shrd_uchar m_data = shrd_uchar(new uchar[bufsize * sizeof(uchar)]);
		fread(m_data.get(), 1, bufsize, fp);
		/* close the file pointer */
		fclose(fp);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:			
			return false;
		}

		// Create one OpenGL texture
		glGenTextures(1, &m_GLId);
		
		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, m_GLId);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		/* load the mipmaps */
		for (unsigned int level = 0; level < mipMapCount && (m_width || m_height); ++level)
		{
			unsigned int size = ((m_width + 3) / 4)*((m_height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, m_width, m_height,
				0, size, m_data.get() + offset);

			offset += size;
			m_width /= 2;
			m_height /= 2;
		}	
		
		glBindTexture(GL_TEXTURE_2D, 0);
		return true;

	}
}