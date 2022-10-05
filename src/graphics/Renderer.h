#pragma once
#include "Texture.h"
#include "../maths/Maths.h"
#include "entt/entt.hpp"

class Renderer
{
public:
	static Renderer& GetInstance()
	{
		static Renderer instance; 
		return instance;
	}

	Renderer(Renderer const&) = delete;
	void operator=(Renderer const&) = delete;

	static void Init() { GetInstance().init(); }

	static void Render(entt::registry& registry) { GetInstance().render(registry); }

	static SDL_Renderer* GetNativeRenderer() { return GetInstance().getNativeRenderer(); }
	static void RenderClear(Vec4 color) { GetInstance().renderClear(color); }
	static void RenderPresent() { GetInstance().renderPresent(); }
	bool debug = false;
private:
	Renderer();

	void init();

	void render(entt::registry& registry);

	SDL_Renderer* getNativeRenderer();
	void renderClear(Vec4 color);
	void renderPresent();

	SDL_Renderer* m_Renderer;
};

