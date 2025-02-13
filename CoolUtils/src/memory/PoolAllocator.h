#pragma once
#include "Allocator.h"
#include "../Logger.h"

namespace co {
	struct ChunkNode {
		ChunkNode* next;
	};

	class PoolAllocator : public IAllocator {
	public:
		PoolAllocator(const size_t& size, const size_t& chunckSize, const co_align_t& chunkAlignment);
		~PoolAllocator();
		void* Allocate(const size_t& size=0, const co_align_t& alignment=0) override;
		void Free(void* block) override;
		void FreeAll() override;

	private:
		size_t m_chunckSize;
		ChunkNode* p_header;
	};

}