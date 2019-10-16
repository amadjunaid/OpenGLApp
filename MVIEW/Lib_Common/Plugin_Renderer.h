#pragma once
#ifndef PLUGIN_RENDERER_H
#define PLUGIN_RENDERER_H

#include "CommonUtils.h"
#include "Threadable.h"
#include "MObject.h"
#include <queue>
#include "..\Externals\concurrentqueue.h"

//#include "Param.h"



namespace mview {
	class SceneManager;
	typedef std::shared_ptr<SceneManager> shrd_SceneManager;
	//************
	//Base class for renderering plugins
	//************
	enum DATA_ACTION { DONOTHING, ADD, REPLACE, CHANGEPARAM, REMOVE };
	struct DLLEXPORT DataRefresh {
		DATA_ACTION action;		
		shrd_MObject obj;
		int modifiedParam;
		DataRefresh(): action(DATA_ACTION::DONOTHING), obj(nullptr) {}
		DataRefresh(const DATA_ACTION& _action, const shrd_MObject _obj) : action((DATA_ACTION)_action), obj(_obj) {}
		DataRefresh(const shrd_MObject _obj, const int& _modParam) : obj(_obj), modifiedParam(_modParam) { action = CHANGEPARAM; }
		DataRefresh(MObject* _objPtr, const int& _modParam) : obj(shrd_MObject(_objPtr)), modifiedParam(_modParam) { action = CHANGEPARAM; }
	};	
	typedef std::shared_ptr<DataRefresh> shrd_DataRefresh;

	class DLLEXPORT Plugin_Renderer : public Threadable
	{
	protected:

		//Rendered data.. format dependent on the specific renderer e.g. and RGB image
				
		ThreadedRenderedData m_threadedRenderedData[2];				
		shrd_SceneManager g_sceneManager;

		DWORD m_startTime = DWORD(0);
		longInt m_frameNumber = 0;
		
		
		virtual void OnResize() = 0;
		virtual void OnDataRefresh() = 0;
		
		static bool m_doResize;
		//static bool m_doDataRefresh;

		static moodycamel::ConcurrentQueue<shrd_DataRefresh> m_dataRefreshList;
		
		
	public:
		
		shrd_int g_width;
		shrd_int g_height;
		bool m_startRendering = false;
		
		Plugin_Renderer();

		Plugin_Renderer(shrd_int width, shrd_int height);

		~Plugin_Renderer();

		virtual void OnShow() = 0;
		virtual void Destroy() = 0;

		virtual void OnPaint() = 0;
		virtual void OnMouseMove(int cx, int cy);

		static void DoResize();

		moodycamel::ConcurrentQueue<shrd_DataRefresh>& GetDataRefresh();
		static void AddToDataRefresh(const shrd_DataRefresh& dataRefresh);
		//static void DoDataRefresh();
		
		virtual void executable() = 0;
		
		//Process any events signalled from the front end
		virtual void ProcessEvents(); 

		//Provides rendered data
		ThreadedRenderedData* GetThreadedRenderedData();

	};

	

	typedef std::shared_ptr<mview::Plugin_Renderer> shrd_Plugin_Renderer;	
}

#endif /*PLUGIN_RENDERER_H*/