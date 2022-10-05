#include "pch.h"
#include "Log.h"
#include "../utils/FileUtils.h"

std::vector<std::string> Log::m_LogBuffer;
HANDLE Log::m_Console;

void Log::Init()
{
	m_Console = GetStdHandle(STD_OUTPUT_HANDLE);
	Log::LogInfo("Log system initialized successfully.");
}

void Log::Quit()
{
	SaveToDisc();
	SetConsoleTextAttribute(m_Console, 15);
}

void Log::SaveToDisc()
{
	std::string log;

	for (size_t i = 0; i < m_LogBuffer.size(); i++)
	{
		log += m_LogBuffer[i] + "\n";
	}

	FileUtils::WriteFile(log, "src/log.txt");
	m_LogBuffer.clear();
}

void Log::LogTrace(std::string text)
{
	std::string logEntry = "[" + getHMSTime() + "] " + text;
	SetConsoleTextAttribute(m_Console, 15);
	std::cout << logEntry << std::endl;
	m_LogBuffer.push_back(logEntry);
}

void Log::LogInfo(std::string text)
{
	std::string logEntry = "[" + getHMSTime() + "] " + text;
	SetConsoleTextAttribute(m_Console, 10);
	std::cout << logEntry << std::endl;
	m_LogBuffer.push_back(logEntry);
}

void Log::LogError(std::string text)
{
	std::string logEntry = "[" + getHMSTime() + "]" + "(Error) " + text;
	SetConsoleTextAttribute(m_Console, 12);
	std::cout << "[" << getHMSTime() << "] " <<"(Error) " << text << std::endl;
	m_LogBuffer.push_back(logEntry);
}

void Log::LogWarning(std::string text)
{
	std::string logEntry = "[" + getHMSTime() + "]" + "(Warning) " + text;
	SetConsoleTextAttribute(m_Console, 14);
	std::cout << "[" << getHMSTime() << "] " << "(Warning) " << text << std::endl;
	m_LogBuffer.push_back(logEntry);
}

void Log::LogCritical(std::string text)
{
	std::string logEntry = "[" + getHMSTime() + "]" + "(CRITICAL) " + text;
	SetConsoleTextAttribute(m_Console, 4);
	std::cout << "[" << getHMSTime() << "] " << "(CRITICAL) " << text << std::endl;
	m_LogBuffer.push_back(logEntry);
}

std::string Log::getHMSTime()
{
	char sysTimeStr[13] = {};
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	sprintf_s(sysTimeStr,
		"%u:%02u:%02u",
		systemTime.wHour,
		systemTime.wMinute,
		systemTime.wSecond);

	return std::string(sysTimeStr);
}
