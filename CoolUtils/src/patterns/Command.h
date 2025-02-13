#pragma once
#include <functional>
namespace co {

	template <typename T>
	class ICommand {
	public:
		virtual void Run() = 0;
		virtual void SetCommand(T commandObj) = 0;
	};

	class FnCommand :public ICommand<std::function<void()>> {
	public:
		using FnType = std::function<void()>;

		FnCommand(FnType function) : _function(function) {};
		FnCommand() {};

		void Run() override {
			_function();
		}

		void SetCommand(FnType function) {
			_function = function;
		}

	private:
		std::function<void ()> _function;
	};


}