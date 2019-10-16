#include "Threadable.h"
#include <memory>

namespace mview{

	Threadable::Threadable()
	{
		
	}

	Threadable::~Threadable()
	{
		
	}

	void Threadable::execute()
	{
		m_thread = std::thread(&Threadable::executable, this);	
		
		//Return after initialization
		while (!m_initialized);		
	}

	void Threadable::terminate()
	{
		isTerminated = true;
		m_thread.join();
	}


	void Threadable::ThreadSleep(int milliseconds)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
	}
	
}
