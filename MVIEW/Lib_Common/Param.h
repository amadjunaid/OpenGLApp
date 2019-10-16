#pragma once
#ifndef UPDATABLEPARAM_H
#define UPDATABLEPARAM_H
#include "Plugin_Renderer.h"
#include "MObject.h"

namespace mview
{
	template<class T>
	class DLLEXPORT Param: public BaseParam
	{
	private:		
		T m_value;
		std::vector<std::function<void()>> OnAssignCallbacks;		
	public:
		int m_usage;
		
		Param() { m_value = T(); m_usage = -1;  }
		Param(T value, int usage, std::function<void()> onAssignCallback_ = nullptr)
		{
			m_value = value;
			m_usage = usage;					
			OnAssignCallbacks.push_back(onAssignCallback_);			
		}

		void AddAssignmentCallBack(std::function<void()> callback_)
		{
			OnAssignCallbacks.push_back(callback_);
		}

		Param& operator=(const T& newvalue) {
			m_value = newvalue;
			for (size_t i = 0; i < OnAssignCallbacks.size(); i++)
			{
				if (OnAssignCallbacks.at(i))
					OnAssignCallbacks.at(i)();
			}
			if ( m_container ){				
				shrd_DataRefresh datarefresh(new DataRefresh(m_container, m_usage));				
				Plugin_Renderer::AddToDataRefresh(datarefresh);				
			}
			else {
				Logger::Message(LOG_SEVERITY::LOG_WARNING, "No container found for param, do not forget to activate params(add in params list) in the container. Changes cannot propogate to dependent modules.");
			}
			return *this;
		}

		operator T() const {			
			return m_value;
		}

		T Get() {
			return m_value;
		}
	};

	typedef Param<glm::vec3> Param_vec3;
	typedef std::shared_ptr<Param_vec3> shrd_Param_vec3;
	typedef Param<int> Param_int;
	typedef std::shared_ptr<Param_int> shrd_Param_int;
	typedef Param<float> Param_float;
	typedef std::shared_ptr<Param_float> shrd_Param_float;
	typedef Param<glm::mat4> Param_mat4;
	typedef std::shared_ptr<Param_mat4> shrd_Param_mat4;

	template<class T>
	using shrd_Param_T = std::shared_ptr<Param<T>>;
}
#endif // !UPDATABLEPARAM_H
