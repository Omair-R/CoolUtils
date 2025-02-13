#pragma once
#include <memory>
#include <string>
#include <mutex>

#include "utils.h"

namespace co {

	template <typename Mixin>
	class NaiveSinglton : public NonCopyable {
	public: 
		static Mixin& GetInstance() {
			static Mixin instence; 
			return instence;
		}
	};

	template <typename Mixin>
	class SafeAbstractSinglton : NonCopyable {
	private:
		static std::shared_ptr<Mixin> p_instance;
		
	protected:
		SafeAbstractSinglton() = default;
		~SafeAbstractSinglton() = default;
		static std::mutex _mutex;

	public:
		static std::shared_ptr<Mixin> GetInstance()
		{
			std::lock_guard<std::mutex> lock(_mutex);

			if (p_instance == nullptr) {
				p_instance = std::make_shared<Mixin>();
			}
			return p_instance;
		}

	};

	template <typename Mixin>
	std::shared_ptr<Mixin> SafeAbstractSinglton<Mixin>::p_instance{nullptr};

	template <typename Mixin>
	std::mutex SafeAbstractSinglton<Mixin>::_mutex;

}
