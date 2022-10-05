#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	
}

GameObject Scene::CreateGameObject()
{
	GameObject gameObject = GameObject(_registry.create(), this);
	return gameObject;
}

void Scene::DestroyGameObject(GameObject gameObject)
{
	_registry.destroy(gameObject);
}
