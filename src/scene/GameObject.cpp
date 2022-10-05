#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(entt::entity handle, Scene* scene)
	: m_Handle{ handle }, m_Scene{ scene } {}
