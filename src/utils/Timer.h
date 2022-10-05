#pragma once
#include <SDL.h>

class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Pause();
	void Unpause();

	uint32_t GetTime();

	bool IsStarted();
	bool IsPaused();

private:
	uint32_t m_StartTime;
	uint32_t m_PausedTime;

	bool m_IsStarted;
	bool m_IsPaused;
};

