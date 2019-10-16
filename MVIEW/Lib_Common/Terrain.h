#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "CommonUtils.h"
#include "TriangleMesh.h"

namespace mview
{
	struct TerrainParams {
		std::string heightFieldFile = "../Data/heightmap.bmp";
		std::string terrainTextureFile = "../Data/Textures/test.tga";
		int width = 100;
		int height = 100;
		float scale = 12.f;
		glm::vec3 color = glm::vec3(1.f, 1.f, 1.f);
		float spacing = 1.f;

		TerrainParams() {}
		TerrainParams(const std::string& _heightFile, const std::string& _textureFile, const int&  _width, const int& _height, const float& _scale) :
			heightFieldFile(_heightFile), terrainTextureFile(_textureFile), width(_width), height(_height), scale(_scale)
		{}
	};

	enum TERRAIN_TYPE { TT_GRID, TT_TRIMESH };

	class DLLEXPORT Terrain: public TriangleMesh
	{
		
		struct HeightMapType
		{
			float x, y, z;
		};

		
	public:
		TERRAIN_TYPE m_terrainType = TERRAIN_TYPE(-1);
		bool m_initialized = false;
		TerrainParams m_data;		
		int m_numLines;		
		
		bool m_isIndexed = false;		
		Terrain();
		Terrain(const TerrainParams& data);
		~Terrain();
	private:
		bool LoadBitmapHeightMap();
		void LoadDummyData();
		void SetTerrainCoordinates();

		HeightMapType* m_heightMap;
	};

	typedef std::shared_ptr<Terrain> shrd_Terrain;

}
#endif // !TERRAIN_H

