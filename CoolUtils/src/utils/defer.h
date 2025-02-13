#pragma once
#include <functional>
#include "../patterns/utils.h"

namespace co {
	
	using VoidFunction = std::function<void()>;

	class Deferer : NonMoveOrCopyable {
	public:

		Deferer(VoidFunction&& function) : m_function(std::forward<decltype(function)>(function)) {}
		~Deferer() { m_function(); }

		static Deferer DeferFunction(VoidFunction&& f) {
			return Deferer(std::forward<VoidFunction>(f));
		}

	private:
		VoidFunction m_function;
	};

}

#define COMBINE_SYM(x, l) x##l
#define UNIQUE_NAME_GEN(l) COMBINE_SYM(defer_, l)
#define CO_defer(_lambda) [[maybe_unused]] auto UNIQUE_NAME_GEN(__LINE__) = co::Deferer::DeferFunction([&]() {_lambda;})