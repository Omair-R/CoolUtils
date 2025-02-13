#include "ArenaAllocator.h"

namespace co {

	ArenaAllocator::ArenaAllocator(const size_t& size) :IAllocator(size), m_currentOffset(0) {}

	ArenaAllocator::~ArenaAllocator(){}

	void* ArenaAllocator::Allocate(const size_t& size, const co_align_t& alignment) {

		if (size == 0 || alignment == 0)
			throw std::bad_alloc();

		const uintptr_t beginPtr = reinterpret_cast<uintptr_t>(p_memoryBegin);
		uintptr_t currentPosition = beginPtr + m_currentOffset;

		currentPosition = Align(currentPosition, alignment);

		const uintptr_t padding = currentPosition - (beginPtr + m_currentOffset);

		if (currentPosition + size > beginPtr + m_memorySize)
			throw std::bad_alloc();

		m_currentOffset += size + padding;

		return placePointer(currentPosition);
		
	}

	void ArenaAllocator::Free(void* block) {
		//TODO: debug message
	}

	void ArenaAllocator::FreeAll() {
		m_currentOffset = 0;
	}

	size_t ArenaAllocator::GetOffsetMarker()
	{
		return m_currentOffset;
	}

}