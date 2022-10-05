#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Window
{
public:
	static Window& GetInstance()
	{
		static Window instance;
		return instance;
	}

	Window(Window const&) = delete;
	void operator=(Window const&) = delete;

	static void Init() { GetInstance().init(); }
	static SDL_Window* GetNativeWindow() { return GetInstance().getNativeWindow(); }
	static const char* GetTitle() { return GetInstance().getTitle(); }
	static int GetWidth() { return GetInstance().getWidth(); }
	static int GetHeight() { return GetInstance().getHeight(); }
	static void SetTitle(const char* title) { GetInstance().setTitle(title); }
	static void SetIcon(SDL_Surface* icon) { GetInstance().setIcon(icon); }
	static void SetFullScreen() { GetInstance().setFullScreen(); }

private:
	Window() {}

	void init();
	SDL_Window* getNativeWindow();
	const char* getTitle();
	int getWidth();
	int getHeight();
	void setTitle(const char* title);
	void setIcon(SDL_Surface* icon);
	void setFullScreen();

	SDL_Window* m_Window = NULL;
	const char* m_Title = "";
	int m_Width = 0;
	int m_Height = 0;
	SDL_Surface icon;
};

