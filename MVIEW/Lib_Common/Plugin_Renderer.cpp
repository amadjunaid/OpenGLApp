#include "Plugin_Renderer.h"

namespace mview {
	
	//bool Plugin_Renderer::m_doDataRefresh = false;
	bool Plugin_Renderer::m_doResize = false;
	moodycamel::ConcurrentQueue<shrd_DataRefresh> Plugin_Renderer::m_dataRefreshList;

	moodycamel::ConcurrentQueue<shrd_DataRefresh>& Plugin_Renderer::GetDataRefresh()
	{
		return m_dataRefreshList;
	}

	void Plugin_Renderer::AddToDataRefresh(const shrd_DataRefresh& dataRefresh)
	{
		//Logger::Message(LOG_INFO, "Adding DataRefresh");
		m_dataRefreshList.enqueue(dataRefresh);
	}

	Plugin_Renderer::Plugin_Renderer()
	{
		m_threadedRenderedData[RenderBuffers::FRONT].m_dataPtr = nullptr;
		m_threadedRenderedData[RenderBuffers::BACK].m_dataPtr = nullptr;
	}

	Plugin_Renderer::Plugin_Renderer(shrd_int width, shrd_int height) :
		Plugin_Renderer()
	{
		g_width = width;
		g_height = height;
	}


	Plugin_Renderer::~Plugin_Renderer()
	{
			
	}

	void Plugin_Renderer::OnMouseMove(int cx, int cy)
	{
	}

	void Plugin_Renderer::DoResize()
	{
		m_doResize = true;
	}

	/*void Plugin_Renderer::DoDataRefresh()
	{
		m_doDataRefresh = true;
	}*/

	void Plugin_Renderer::ProcessEvents()
	{
		//Checks signals and processes event.. add more events in the same manner... using a signal variable and processing function
		if (m_doResize) {
			OnResize();
			m_doResize = false;
		}

		/*if (GetDataRefresh().peek()) {*/
			OnDataRefresh();
			//m_doDataRefresh = false;
		/*}*/
	}

	ThreadedRenderedData* Plugin_Renderer::GetThreadedRenderedData()
	{
		return m_threadedRenderedData;
	}
}
