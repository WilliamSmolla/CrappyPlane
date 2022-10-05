#pragma once
#include "entt/entt.hpp"
#include "scene/GameObject.h"

class CollisionManager
{
public:
	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;

	static void Init() { GetInstance().init(); }
	static void Integrate(entt::registry& registry, GameObject& player) { GetInstance().integrate(registry, player); }
	static bool IsColliding() { return GetInstance().isColliding(); }
private:
	CollisionManager(){}

	void init();
	void integrate(entt::registry& registry, GameObject& player);
	bool isColliding() { return _isColliding; }
	bool _isColliding = false;
};

