#pragma once
#include "Allocator.h"

namespace co {

	class StackAllocator : IAllocator
	{
	public:
		typedef co_byte_t Header;

		StackAllocator(const size_t& size);
		~StackAllocator();

		void* Allocate(const size_t& size, const co_align_t& alignment) override;
		void Free(void* block) override;
		void FreeAll() override;
		size_t GetOffsetMarker();

	private:
		size_t m_currentOffset;
	};
}

