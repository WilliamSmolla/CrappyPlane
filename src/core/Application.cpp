#include "pch.h"
#include "Application.h"
#include "Log.h"

Application::Application()
    : m_IsRunning{ true }
{
    srand(static_cast<unsigned>(time(0)));

	Log::Init();
	initSDL();
    Window::Init();
    Renderer::Init();
    AssetManager::Init();
    CollisionManager::Init();
}

void Application::Run()
{
    SDL_Event event;

    float lastFrameTime = SDL_GetTicks() - m_FrameTime;
    float timeAccumulator = 0;

    while (m_IsRunning)
    {
        float frameTime = SDL_GetTicks();
        float deltaTime = frameTime - lastFrameTime;

        while (SDL_PollEvent(&event))
        {
            HandleEvents(event);
        }

        if (deltaTime > 100) deltaTime = 100;

        timeAccumulator += deltaTime;

        while (timeAccumulator >= m_FrameTime)
        {
            Update(m_FrameTime);
            timeAccumulator -= m_FrameTime;
        }

        Update(timeAccumulator);

        timeAccumulator = 0;

        Render();       

        int wait = frameTime + m_FrameTime - SDL_GetTicks();

        if (wait < 0)
        {
            std::string waitTime = std::to_string(-wait);
            Log::LogWarning("Lag of " + waitTime + " ms");
        }
        else
        {
            SDL_Delay(wait);
        }

        lastFrameTime = frameTime;
    }

    Log::Quit();
}

void Application::initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
		Log::LogCritical("Failed to initialize SDL " + std::string(SDL_GetError()));
		exit(EXIT_FAILURE);
	}
	else
	{
		Log::LogInfo("SDL_VID initialized successfully.");
	}

	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
        Log::LogCritical("Failed to initialize SDL_IMG: " + std::string(IMG_GetError()));
        exit(EXIT_FAILURE);
	}
    else
    {
        Log::LogInfo("SDL_IMG initialized successfully.");
    }

    if (SDL_Init(SDL_INIT_AUDIO) < 0 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Log::LogCritical("Failed to initialize SDL_MIX: " + std::string(SDL_GetError()));
        exit(EXIT_FAILURE);
    }

    else
    {
        Log::LogInfo("SDL_MIX initialized successfully");
    }

    if (TTF_Init() < 0)
    {
        Log::LogCritical("Failed to initialize SDL_TTF: " + std::string(TTF_GetError()));
        exit(EXIT_FAILURE);
    }

    else
    {
        Log::LogInfo("SDL_TTF initialized successfully");
    }
}
