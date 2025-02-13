#pragma once
#include <cstdint>
#include <memory>

#define co_align_t unsigned long long
#define co_byte_t unsigned char

namespace co {

	inline uintptr_t Align(const uintptr_t& ptr, const co_align_t& align);

	template <typename T = void>
	inline T* placePointer(const uintptr_t& position);

	class IAllocator {
	public:
		IAllocator(const size_t& size);
		~IAllocator();

		virtual void* Allocate(const size_t& size, const co_align_t& alignment) = 0;
		virtual void Free(void* block) = 0;
		virtual void FreeAll() = 0;

	protected:
		size_t m_memorySize;
		void* p_memoryBegin;
	}; 
}

#include "Allocator_T.h"