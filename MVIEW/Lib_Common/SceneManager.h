#pragma once
#ifndef SCENECONTROLLER_H
#define SCENECONTROLLER_H

#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "MaterialLib.h"

namespace mview {
	
	//************
	//SceneManager class. Responsible to add, modify or delete scene data and keep all the modules using that data(e.g. the renderer) in-sync
	//************	
	class DLLEXPORT SceneManager
	{
		//Global objects list
		static shrd_MObjectList m_MObjectList;
		//static shrd_MaterialLib m_MaterialLib;
		
		static shrd_Camera m_cam;		

	public:
		//SceneManager();
		//SceneManager(shrd_Camera cam);
		~SceneManager();

		static void AddObject(shrd_MObject object);
		static void ReplaceData(int objIdx);
		static void ChangeData(int objIdx, int _param);
		static void DeleteObject( shrd_MObject object );
		
		//Very important to be called after every data modification to reflect changes to other systems using the data
		//void DoDataRefresh();		
		static void SetCam(const shrd_Camera&);
		static const shrd_Camera& getCam();
		//static const shrd_MaterialLib& getMaterialLib();
	};

	typedef std::shared_ptr<SceneManager> shrd_SceneManager;
}
#endif // !SCENECONTROLLER_H