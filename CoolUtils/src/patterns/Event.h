#pragma once
#include <string>
#include <functional>
#include <unordered_map>

#include "utils.h"

namespace co {

	class Event {
	public:
		static Event Empty(){ return Event(); }
	};

	template <std::derived_from<Event> E>
	class IEventHandler {
	public:
		using ListenerFnType = void (*)(const E&);

		virtual void Subscribe(ListenerFnType listener) = 0;
		virtual void Invoke(const E& event) = 0;
	};

	template <std::derived_from<Event> E>
	class MonoEventHandler: public IEventHandler<E> {
	public:
		using ListenerFnType = void (*)(const E&);

		MonoEventHandler() = default;
		void Subscribe(ListenerFnType listener) override;
		void Invoke(const E& event) override;

	private:
		ListenerFnType _listener;
	};

	template <std::derived_from<Event> E>
	class ListEventHandler : public IEventHandler<E> {
	public:
		using ListenerFnType = void (*)(const E&);
		using fnUID = size_t;
		ListEventHandler() = default;
		void Subscribe(ListenerFnType listener) override;
		void Unsubscribe(ListenerFnType listener);
		void Invoke(const E& event) override;

	private:
		fnUID GetFunctionHash(ListenerFnType fn) const;
		std::unordered_map<fnUID, ListenerFnType> _listeners{};
	};


}

#include "Event_T.h"