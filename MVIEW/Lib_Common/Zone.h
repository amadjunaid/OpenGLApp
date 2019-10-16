#pragma once
#ifndef ZONE_H
#define ZONE_H

#include "CommonUtils.h"
#include "SceneObject.h"
#include "Terrain.h"
#include "Param.h"
#include "Texture.h"

namespace mview
{
	class DLLEXPORT Zone: public MObject
	{
	protected:
		std::vector<shrd_Terrain> m_terrainList;	
		shrd_mat4 m_pose;
		shrd_MaterialLib m_matLib;
		shrd_TextureLib m_texLib;
	public:
		shrd_Param_T<RENDER_MODE> m_renderMode;
		

		const std::vector<shrd_Terrain>& getTerrainList();
		shrd_mat4 getPose();
		
		Zone();
		void AddTerrain(const TerrainParams& terrainParams);

		const shrd_MaterialLib GetMatLib();
		const shrd_TextureLib GetTexLib();

		~Zone();

		enum {PM_RENDERMODE, COUNT};
	};

	typedef std::shared_ptr<Zone> shrd_Zone;
}

#endif // !ZONE_H