#pragma once
#include <functional>

namespace co {
	class NonCopyable {
	public:
		NonCopyable() = default;
		~NonCopyable() = default;

		NonCopyable(NonCopyable& other) = delete;
		NonCopyable& operator=(NonCopyable& other) = delete;
	};

	class NonMoveable {
	public:
		NonMoveable() = default;
		~NonMoveable() = default;

		NonMoveable(NonMoveable&& other) = delete;
		NonMoveable& operator=(NonMoveable&& other) = delete;
	};

	class NonMoveOrCopyable {
	public:
		NonMoveOrCopyable() = default;
		~NonMoveOrCopyable() = default;

		NonMoveOrCopyable(NonMoveOrCopyable& other) = delete;
		NonMoveOrCopyable& operator=(NonMoveOrCopyable& other) = delete;
		NonMoveOrCopyable(NonMoveOrCopyable&& other) = delete;
		NonMoveOrCopyable& operator=(NonMoveOrCopyable&& other) = delete;
	};

	
}