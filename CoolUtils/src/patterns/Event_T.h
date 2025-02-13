#pragma once
#include <memory>

namespace co {

	//==============MonoEventHandler===================
	template <std::derived_from<Event> E>
	inline void MonoEventHandler<E>::Subscribe(ListenerFnType listener)
	{
		_listener = listener;
	}

	template <std::derived_from<Event> E>
	inline void MonoEventHandler<E>::Invoke(const E& event)
	{
		_listener(event);
	}

	//==============ListEventHandler===================
	template<std::derived_from<Event> E>
	inline void ListEventHandler<E>::Subscribe(ListenerFnType listener)
	{
		_listeners[GetFunctionHash(listener)] = listener;
	}

	template<std::derived_from<Event> E>
	inline void ListEventHandler<E>::Unsubscribe(ListenerFnType listener)
	{
		fnUID fnID = GetFunctionHash(listener);
		if (_listeners.find(fnID) != _listeners.end())
			_listeners.erase(fnID);
	}

	template<std::derived_from<Event> E>
	inline void ListEventHandler<E>::Invoke(const E& event)
	{
		for (const auto& [_, listener] : _listeners)
			listener(event);

	}
	template<std::derived_from<Event> E>
	ListEventHandler<E>::fnUID ListEventHandler<E>::GetFunctionHash(ListenerFnType fn) const {
		static std::hash<ListenerFnType> hasher;
		return hasher(fn);
	}

}