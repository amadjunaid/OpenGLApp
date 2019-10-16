
#ifndef COMMONUTILS_LIB_OPENGL
#define COMMONUTILS_LIB_OPENGL
#include <CommonUtils.h>


#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>
#include <algorithm>
#include <SceneManager.h>


#ifdef LIB_OPENGL_EXPORTS
#define LIB_OPNEGL_API DllExport
#else
#define LIB_OPENGL_API DLLIMPORT 
#endif

//#define GL_USEDEBUGWINDOW
//#define GL_SHOWFRAMETIME

#define GL_USEPBO




//************
//Contains common structs, functions etc for this module.
//************	
namespace mview {

	

	template <class T>
	struct SpecialCompare : public std::unary_function<longInt, bool>
	{
		explicit SpecialCompare(const longInt &baseline) : baseline(baseline) {}
		bool operator() (const T &arg)
		{
			return arg->m_globalId == baseline;
		}
		longInt baseline;
	};


	struct VertexAttributeBuffer {
		GLuint m_id; //ID for use with Open GL
		int m_type;

		VertexAttributeBuffer(GLuint id, int size, int type) : m_id(id), m_type(type)
		{
		}

	};
}





#endif // !COMMONUTILS_LIB_OPENGL

