#include "SceneManager.h"
#include "Plugin_Renderer.h"
#include "CommonUtils.h"


namespace mview {

	shrd_MObjectList SceneManager::m_MObjectList = shrd_MObjectList(new MObjectList());
	//shrd_MaterialLib SceneManager::m_MaterialLib = shrd_MaterialLib(new MaterialLib());
	shrd_Camera SceneManager::m_cam = nullptr;

	/*SceneManager::SceneManager()
	{
		m_MObjectList.reset(new MObjectList());
		m_MaterialLib.reset(new MaterialLib());
	}

	SceneManager::SceneManager(shrd_Camera cam):
		SceneManager()
	{
		m_cam = cam;		

		m_MObjectList->push_back(m_cam);
		m_MObjectList->back()->ActivateParams();
	}*/


	SceneManager::~SceneManager()
	{
	}

	void SceneManager::AddObject(shrd_MObject object)
	{
		if (object->m_initialized) 
			m_MObjectList->push_back(object);

		m_MObjectList->back()->ActivateParams();
		//Sync with VIEW
		Plugin_Renderer::AddToDataRefresh(shrd_DataRefresh(new DataRefresh(DATA_ACTION::ADD, object)));
	}

	void SceneManager::ReplaceData(int objIdx)
	{
		if (objIdx < m_MObjectList->size())
			Plugin_Renderer::AddToDataRefresh(shrd_DataRefresh(new DataRefresh(DATA_ACTION::REPLACE, m_MObjectList->at(objIdx))));
	}

	void SceneManager::ChangeData(int objIdx, int param)
	{
		if (objIdx < m_MObjectList->size())
			Plugin_Renderer::AddToDataRefresh(shrd_DataRefresh(new DataRefresh(m_MObjectList->at(objIdx), param)));
	}

	void SceneManager::DeleteObject(shrd_MObject object)
	{		
		//Remove from the global containers now
		m_MObjectList->erase(std::find(m_MObjectList->begin(), m_MObjectList->end(), object));
		
		//Remove local copies from the renderers if being used		
		Plugin_Renderer::AddToDataRefresh(shrd_DataRefresh(new DataRefresh(DATA_ACTION::REMOVE, object)));
	}

	
	/*void SceneManager::DoDataRefresh()
	{
		Plugin_Renderer::DoDataRefresh();
	}*/
	
	void SceneManager::SetCam(const shrd_Camera& cam)
	{
		m_cam = cam;
		m_MObjectList->push_back(m_cam);
		m_MObjectList->back()->ActivateParams();
	}

	/*const shrd_MObjectList & SceneManager::getMObjectList()
	{
		return m_MObjectList;
	}*/
	const shrd_Camera & SceneManager::getCam()
	{
		return m_cam;
	}

	/*const shrd_MaterialLib & SceneManager::getMaterialLib()
	{
		return m_MaterialLib;
	}*/
}
