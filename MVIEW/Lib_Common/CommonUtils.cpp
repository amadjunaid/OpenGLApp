#include "CommonUtils.h"

namespace mview {

	void DLLEXPORT QuatToMat4(glm::mat4& mat, const float& x, const float& y, const float& z, const float& w)
	{
		float x2 = x*x;
		float y2 = y*y;
		float z2 = z*z;
		float xy = x*y;
		float xz = x*z;
		float yz = y*z;
		float wx = w*x;
		float wy = w*y;
		float wz = w*z;

		mat[0].x = 1 - 2 * y2 - 2 * z2;
		mat[0].y = 2 * xy + 2 * wz;
		mat[0].z = 2 * xz - 2 * wy;

		mat[1].x = 2 * xy - 2 * wz;
		mat[1].y = 1 - 2 * x2 - 2 * z2;
		mat[1].z = 2 * yz + 2 * wx;

		mat[2].x = 2 * xz + 2 * wy;
		mat[2].y = 2 * yz - 2 * wx;
		mat[2].z = 1 - 2 * x2 - 2 * y2;
	}

	Logger::Logger()
	{
	}


	Logger::~Logger()
	{
	}

	void Logger::Message(int logSeverity, std::string msg)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::string logSeverity_str;
		switch (logSeverity) {
		case LOG_INFO:
			logSeverity_str = "Info: ";
			SetConsoleTextAttribute(hConsole, 0x07);
			break;
		case LOG_WARNING:
			logSeverity_str = "Warning: ";
			SetConsoleTextAttribute(hConsole, 0x0E);
			break;
		case LOG_ERROR:
			logSeverity_str = "ERROR: ";
			SetConsoleTextAttribute(hConsole, 0x0C);
			break;
		}

		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time

		int Day = localTime->tm_mday;
		int Month = localTime->tm_mon + 1;
		int Year = localTime->tm_year + 1900;
		int Hour = localTime->tm_hour;
		int Min = localTime->tm_min;
		int Sec = localTime->tm_sec;

		std::cout << "[";
#ifdef LOG_DATE
		std::cout << Day << "." << Month << "." << Year << "  ";
#endif // LOG_Da 
		std::cout << Hour << ":" << Min << ":" << Sec << "] ";

		std::cout << logSeverity_str << msg << std::endl;

		SetConsoleTextAttribute(hConsole, 0x07);
	}

	void Logger::Message(std::string msg)
	{
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		std::string logSeverity_str = "Info: ";
			SetConsoleTextAttribute(hConsole, 0x07);

		time_t currentTime;
		struct tm *localTime;

		time(&currentTime);                   // Get the current time
		localTime = localtime(&currentTime);  // Convert the current time to the local time

		int Day = localTime->tm_mday;
		int Month = localTime->tm_mon + 1;
		int Year = localTime->tm_year + 1900;
		int Hour = localTime->tm_hour;
		int Min = localTime->tm_min;
		int Sec = localTime->tm_sec;

		std::cout << "[";
#ifdef LOG_DATE
		std::cout << Day << "." << Month << "." << Year << "  ";
#endif // LOG_Da 
		std::cout << Hour << ":" << Min << ":" << Sec << "] ";

		std::cout << logSeverity_str << msg << std::endl;

		SetConsoleTextAttribute(hConsole, 0x07);
	}

	/************************************************COLOR CODES
	0x[Background][Foreground]
	0 = Black
	1 = Blue
	2 = Green
	3 = Aqua
	4 = Red
	5 = Purple
	6 = Yellow
	7 = White
	8 = Gray
	9 = Light Blue
	A = Light Green
	B = Light Aqua
	C = Light Red
	D = Light Purple
	E = Light Yellow
	F = Bright White

	//*** See all Colors
	HANDLE hConsole;
	int k;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// you can loop k higher to see more color choices
	for (k = 1; k < 255; k++)
	{
	// pick the colorattribute k you want
	SetConsoleTextAttribute(hConsole, k);
	std::cout << k << " I want to be nice today!" << std::endl;
	}
	*/

	std::string getFileName(const std::string& s) {
		return s.substr(s.find_last_of("/\\")+1);
	}

	std::string GetDirPath(const std::string & s)
	{
		std::string dirPath = s.substr(0, s.find_last_of("/\\"));

		if (dirPath.find("\\") != std::string::npos) return (dirPath + "\\");
		return (dirPath + "/");
	}

	std::string DLLEXPORT CopyFileToString(const std::string & filePath)
	{
		std::ifstream t(filePath);
		std::string str;

		t.seekg(0, std::ios::end);
		str.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

		return str;
	}


}