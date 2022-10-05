#pragma once
#include "entt/entt.hpp"
#include "../maths/Maths.h"
#include "scene/Scene.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(entt::entity handle, Scene* scene);
	GameObject(const GameObject& other) = default;
	
	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		T& component = m_Scene->_registry.emplace<T>
			(m_Handle, std::forward<Args>(args)...);
		return component;
	}
	
	template<typename T>
	void RemoveComponent()
	{
		m_Scene->_registry.remove<T>(m_Handle);
	}

	template<typename T>
	T& GetComponent()
	{
		return m_Scene->_registry.get<T>(m_Handle);
	}

	template<typename T>
	bool HasComponent()
	{
		return m_Scene->_registry.any_of<T>(m_Handle);
	}

	operator bool() const { return m_Handle != entt::null; }
	operator entt::entity() const { return m_Handle; }
	operator uint32_t() const { return (uint32_t)m_Handle; }

	bool operator==(const GameObject& other) const
	{
		return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
	}

	bool operator!=(const GameObject& other) const
	{
		return !(*this == other);
	}

	entt::entity GetHandle() { return m_Handle; }

private:
	entt::entity m_Handle{ entt::null };
	Scene* m_Scene = nullptr;
};

