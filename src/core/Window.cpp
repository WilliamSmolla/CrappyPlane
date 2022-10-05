#include "pch.h"
#include "Window.h"
#include "Log.h"

void Window::init()
{
	m_Window = SDL_CreateWindow("Crappy Plane", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 800, 480, SDL_WINDOW_SHOWN);

	if (m_Window == nullptr) {
		Log::LogCritical("Failed to Initialize Window.");
		exit(EXIT_FAILURE);
	}
	else
	{
		Log::LogInfo("Window created successfully.");
	}
	icon = *IMG_Load("res/starGold.png");
	SDL_SetWindowIcon(m_Window, &icon);
}

SDL_Window* Window::getNativeWindow()
{
	return m_Window;
}

const char* Window::getTitle()
{
	return m_Title;
}

int Window::getWidth()
{
	return m_Width;
}

int Window::getHeight()
{
	return m_Height;
}

void Window::setTitle(const char* title)
{
	SDL_SetWindowTitle(m_Window, title);
	m_Title = title;
}

void Window::setFullScreen()
{
	SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

void Window::setIcon(SDL_Surface* icon)
{
	SDL_SetWindowIcon(m_Window, icon);
}
