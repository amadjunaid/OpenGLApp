
#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#ifndef DEBUG
#pragma warning (disable : 4251)
#endif // DEBUG
//Disable deprecated securtiy messages.. (e.g. getenv() for shader path)
#define _CRT_SECURE_NO_WARNINGS

#define DLLEXPORT   __declspec( dllexport )
#define DLLIMPORT   __declspec( dllimport )
#ifdef LIB_COMMON_EXPORTS
#define LIB_COMMON_API DllExport
#else
#define LIB_COMMON_API DLLIMPORT 
#endif

#include <mutex>
#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


//TODO: Better memory leak detector
//#include <vld.h>

#include <glm/glm.hpp> // http://glm.g-truc.net/
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>

//************
//Common structs, functions, txpedefs etc. defined here
//************	


#define ALMOST_ZERO 1e-6

#define USE_THREADEDRENDEREDDATA

namespace mview {

	enum RenderBuffers { FRONT, BACK, COUNT };

	typedef std::shared_ptr<std::mutex> shrd_mtx;
	typedef unsigned char uchar;
	typedef std::shared_ptr<uchar> shrd_uchar;
	typedef std::lock_guard<std::mutex> Mtx_lock;
	typedef std::shared_ptr<int> shrd_int;
	typedef unsigned int longInt;
	typedef std::shared_ptr<glm::mat4> shrd_mat4;	

	template<typename T>
	bool DLLEXPORT Mat4ToArray16(T a[], const glm::mat4 & mat)
	{

		a[0] = mat[0].x; a[1] = mat[0].y; a[2] = mat[0].z; a[3] = mat[0].w;
		a[4] = mat[1].x; a[5] = mat[1].y; a[6] = mat[1].z; a[7] = mat[1].w;
		a[8] = mat[2].x; a[9] = mat[2].y; a[10] = mat[2].z; a[11] = mat[2].w;
		a[12] = mat[3].x; a[13] = mat[3].y; a[14] = mat[3].z; a[15] = mat[3].w;

		return true;
	}

	template<typename T>
	glm::mat4 DLLEXPORT Array16ToMat4(const T a[])
	{

		return glm::mat4( (float) a[0], (float)a[1], (float)a[2], (float)a[3],
			(float)a[4], (float)a[5], (float)a[6], (float)a[7],
			(float)a[8], (float)a[9], (float)a[10], (float)a[11],
			(float)a[12], (float)a[13], (float)a[14], (float)a[15]
						);
	}

	// convert the quaternion into a rotation matrix
	void DLLEXPORT QuatToMat4(glm::mat4& mat, const float& x, const float& y, const float& z, const float& w);

	//************
	//Provides basic information and error logging capibility with time etc...
	//************
	enum LOG_SEVERITY { LOG_INFO, LOG_WARNING, LOG_ERROR, LS_COUNT };
	//#define LOG_DATE
	class DLLEXPORT Logger
	{
		HANDLE chandle = GetStdHandle(STD_OUTPUT_HANDLE);
	public:
		Logger();
		~Logger();

		//TODO: Output error location
		static void Message(int logSeverity, std::string msg);

		static void Message(std::string msg);
	};

	std::string DLLEXPORT getFileName(const std::string& s); 

	std::string DLLEXPORT GetDirPath(const std::string& s);

	std::string DLLEXPORT CopyFileToString(const std::string& filePath);

	typedef std::shared_ptr<Logger> shrd_Logger;


}

#endif COMMON_UTILS_H