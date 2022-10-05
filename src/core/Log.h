#pragma once
#include <Windows.h>

class Log
{
public:
	static Log& GetInstance()
	{
		static Log instance;
		return instance;
	}

	static void Init();
	static void Quit();
	static void SaveToDisc();

	static void LogTrace(std::string text);
	static void LogInfo(std::string text);
	static void LogError(std::string text);
	static void LogWarning(std::string text);
	static void LogCritical(std::string text);
	
private:
	Log(){}
	static HANDLE m_Console;
	static std::vector<std::string> m_LogBuffer;
	static std::string getHMSTime();
};

