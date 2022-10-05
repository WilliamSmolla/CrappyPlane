#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../core/Window.h"
#include "../graphics/Renderer.h"
#include "AssetManager.h"
#include "SoundManager.h"
#include "physics/CollisionManager.h"

class Application
{
public:
	Application();
	~Application() = default;

	void Run();
	virtual void HandleEvents(const SDL_Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

protected:
	bool m_IsRunning;
	
private:
	void initSDL();
	unsigned int m_FrameTime = 16;
};

