#pragma once
#include "graphics/Renderer.h"
#include "entt/entt.hpp"
#include "core/Window.h"

class GameObject;

class Scene
{
public:
	Scene();
	~Scene();

	GameObject CreateGameObject(); 
	void DestroyGameObject(GameObject gameObject);

	virtual void HandleEvents(const SDL_Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;

protected:
	entt::registry _registry;
	friend class GameObject;
	friend class Renderer;
};
