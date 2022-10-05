#include "pch.h"
#include "Timer.h"

Timer::Timer()
	: m_StartTime{ 0 }, m_PausedTime{ 0 },
	m_IsStarted{ false }, m_IsPaused{ 0 } {}

Timer::~Timer() {}

void Timer::Start()
{
	m_IsStarted = true;
	m_IsPaused = false;
	m_StartTime = SDL_GetTicks();
	m_PausedTime = 0;
}

void Timer::Stop()
{
	m_IsStarted = false;
	m_IsPaused = false;
	m_StartTime = 0;
	m_PausedTime = 0;
}

void Timer::Pause()
{
	if (m_IsStarted && !m_IsPaused)
	{
		m_IsPaused = true;
		m_PausedTime = SDL_GetTicks() - m_StartTime;
		m_StartTime = 0;
	}
}

void Timer::Unpause()
{
	if (m_IsStarted && m_IsPaused)
	{
		m_IsPaused = false;
		m_StartTime = SDL_GetTicks() - m_PausedTime;
		m_PausedTime = 0;
	}
}

uint32_t Timer::GetTime()
{
	uint32_t time = 0;

	if (m_IsStarted)
	{
		if (m_IsPaused)
		{
			time = m_PausedTime;
		}
		else
		{
			time = SDL_GetTicks() - m_StartTime;
		}
	}

	return time;
}

bool Timer::IsStarted()
{
	return m_IsStarted;
}

bool Timer::IsPaused()
{
	return m_IsPaused && m_IsStarted;
}
