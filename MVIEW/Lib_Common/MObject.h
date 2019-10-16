#pragma once
#ifndef MOBJECT_H
#define MOBJECT_H

#include "CommonUtils.h"



namespace mview
{
	class BaseParam;
	typedef std::shared_ptr<BaseParam> shrd_BaseParam;

	enum MOBJECT_TYPE { GENERIC, TRIANGLE_MESH, CAMERA, POINTLIGHT, ZONE, SO_COUNT };

	//************
	//Base class for all objects, contains basic info like name and a global ID
	//************
	class DLLEXPORT MObject: public std::enable_shared_from_this<MObject>
	{
		
	public:
		std::string m_name;
		longInt m_id = 0;
		int m_type = -1;
		bool m_initialized = false;		
		static int m_count;		
		MObject();
		std::shared_ptr<MObject> Get_shrdThis();	
		std::vector<shrd_BaseParam> m_paramList;
		void ActivateParams();
		virtual ~MObject();
	};

	typedef std::shared_ptr<MObject> shrd_MObject;
	typedef std::vector<shrd_MObject> MObjectList;
	typedef std::shared_ptr<MObjectList> shrd_MObjectList;

	//************
	//Base class to help setup the container for params
	//************
	class DLLEXPORT BaseParam
	{
	public:
		shrd_MObject m_container = nullptr;
	};
	
}

#endif // !MOBJECT_H




