#ifndef GLOBJECT_H
#define GLOBJECT_H
#include "CommonUtils_Lib_OpenGL.h"

namespace mview
{

	class DLLEXPORT GLObject
	{
	public:
		longInt m_globalId;
		virtual void UpdateParam(int name) = 0;
		GLObject(longInt globalId);
		~GLObject();
	};
}


#endif // !GLOBJECT_H
