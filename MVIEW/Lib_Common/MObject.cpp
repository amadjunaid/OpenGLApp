#include "MObject.h"

namespace mview {

	int MObject::m_count = 0;

	MObject::MObject()
	{
		m_id = m_count;
		m_count++;
	}

	std::shared_ptr<MObject> MObject::Get_shrdThis()
	{
		
		return shared_from_this();
	}


	void MObject::ActivateParams()
	{
		for (size_t i = 0; i < m_paramList.size(); i++)
		{
			m_paramList.at(i)->m_container = Get_shrdThis();
		}
	}

	MObject::~MObject()
	{

	}

}