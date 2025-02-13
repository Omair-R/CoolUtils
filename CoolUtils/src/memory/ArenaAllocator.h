#pragma once
#include "Allocator.h"

namespace co {
	class ArenaAllocator : IAllocator
	{
	public:
		ArenaAllocator(const size_t& size);
		~ArenaAllocator();

		void* Allocate(const size_t& size, const co_align_t& alignment) override;
		void Free(void* block) override;
		void FreeAll() override;
		size_t GetOffsetMarker();
	private:
		size_t m_currentOffset;
	};
}


