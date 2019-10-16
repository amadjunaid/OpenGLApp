
#ifndef THREADABLE_H
#define THREADABLE_H

#include "CommonUtils.h"
#include <chrono>

namespace mview {

	//************
	//Template class for data(with implicit mutex) shared between threads
	//****
	template<class T>
	class DLLEXPORT ThreadedData
	{
	private:
		shrd_mtx m_mtx;

	public:
		T* m_dataPtr;
		
		ThreadedData()
		{
			m_dataPtr = new T();
			m_mtx = shrd_mtx(new std::mutex());
		}

		~ThreadedData()
		{
			if(m_dataPtr)
				delete m_dataPtr;
			m_dataPtr = nullptr;
			if (m_mtx->try_lock())
				AtomicOpen();
		}

		void AtomicClose()
		{
			m_mtx->lock();			
		}

		bool AtomicCloseOrConitnue()
		{
			return m_mtx->try_lock();
		}

		void AtomicOpen()
		{
			m_mtx->unlock();
		}
	};

	
	typedef ThreadedData<uchar> ThreadedRenderedData;
	//************
	//Base class for adding threading funcitonality to a class
	//************

	class DLLEXPORT Threadable
	{
	private:
		
		std::thread m_thread;

	public:
		//Inidicator that renderer is initialized
		volatile bool m_initialized = false;

		Threadable();
		~Threadable();
		virtual bool Init() = 0;
		
		//Executable function for the thread
		virtual void execute();
		virtual void terminate();
		void ThreadSleep(int milliseconds);
		
	protected:	
		
		bool isTerminated = false;
		virtual void executable() = 0;
		
	};
}

#endif /* THREADABLE_H */