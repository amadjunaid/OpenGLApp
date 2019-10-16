#include "Zone.h"

namespace mview
{
	const std::vector<shrd_Terrain>& Zone::getTerrainList()
	{
		return m_terrainList;
	}
	shrd_mat4 Zone::getPose()
	{
		return m_pose;
	}
	Zone::Zone(): MObject()
	{
		m_type = MOBJECT_TYPE::ZONE;
		m_name = "zone" + m_id;
		m_pose.reset(new glm::mat4(1.0));

		m_renderMode.reset(new Param<RENDER_MODE>(RM_NORMAL, PM_RENDERMODE));

		
		m_paramList.push_back(m_renderMode);

		m_initialized = true;
		//Temporary
		//m_terrainList.push_back(shrd_Terrain(new Terrain(100, 100)));

		m_matLib.reset(new MaterialLib());
		m_texLib.reset(new TextureLib());
	}

	void Zone::AddTerrain(const TerrainParams& terrainParams)
	{
		shrd_Terrain terrain(new mview::Terrain(terrainParams));
		if (terrain->m_initialized) {
			m_terrainList.push_back(terrain);
		}

		terrain->m_textureIDs[TT_DIFFUSE] = m_texLib->AddTexture(TT_DIFFUSE, terrainParams.terrainTextureFile, terrainParams.heightFieldFile);
	}

	const shrd_MaterialLib Zone::GetMatLib()
	{
		return m_matLib;
	}

	const shrd_TextureLib Zone::GetTexLib()
	{
		return m_texLib;
	}


	Zone::~Zone()
	{
		
	}

}
