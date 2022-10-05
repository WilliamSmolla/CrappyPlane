#pragma once

enum class Event
{

};

class EventListener
{
public:
	EventListener() = default;
	virtual ~EventListener() = default;

	virtual void OnEventDispatch(Event event) = 0;
};

class EventDispatcher
{
public:
	EventDispatcher();
	virtual ~EventDispatcher();

	virtual void SubscribeListener(EventListener* listener);
	virtual void UnsubscribeListener(EventListener* listener);

	virtual void DispatchEvent(Event event);

protected:
	std::vector<EventListener*> m_Listeners;
};


