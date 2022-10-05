#include "pch.h"
#include "Event.h"

EventDispatcher::EventDispatcher() {}

EventDispatcher::~EventDispatcher() {}

void EventDispatcher::SubscribeListener(EventListener* listener)
{
	m_Listeners.push_back(listener);
}

void EventDispatcher::UnsubscribeListener(EventListener* listener)
{
	for (size_t i = 0; i < m_Listeners.size(); i++)
	{
		if (m_Listeners[i] == listener)
		{
			m_Listeners.erase(m_Listeners.begin() + i);
			m_Listeners.shrink_to_fit();
			return;
		}
	}
}

void EventDispatcher::DispatchEvent(Event event)
{
	for (auto& listener : m_Listeners)
	{
		listener->OnEventDispatch(event);
	}
}
