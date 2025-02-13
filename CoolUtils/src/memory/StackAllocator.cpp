#include "StackAllocator.h"

namespace co {
	StackAllocator::StackAllocator(const size_t& size) :IAllocator(size), m_currentOffset(0){}

	StackAllocator::~StackAllocator(){}

	void* StackAllocator::Allocate(const size_t& size, const co_align_t& alignment){

		if (size == 0 || alignment == 0)
			throw std::bad_alloc();

		uintptr_t beginPos = reinterpret_cast<uintptr_t>(p_memoryBegin);
		size_t HeaderSize = sizeof(Header);

		uintptr_t currentPosition = beginPos + m_currentOffset + HeaderSize;
		currentPosition = Align(currentPosition, alignment);

		if (currentPosition + size > beginPos + m_memorySize)
			throw std::bad_alloc();

		uintptr_t padding = currentPosition - (beginPos + m_currentOffset) - HeaderSize;

		m_currentOffset += padding + HeaderSize + size;

		Header* header = placePointer<Header>(currentPosition - HeaderSize);
		*header = (Header)padding;

		return placePointer(currentPosition);
	}

	void StackAllocator::Free(void* block){
		if (block == nullptr)
			return;

		if (block < p_memoryBegin ||
			reinterpret_cast<uintptr_t>(block) > reinterpret_cast<uintptr_t>(p_memoryBegin) + m_memorySize)
			throw std::bad_alloc();

		uintptr_t beginPos = reinterpret_cast<uintptr_t>(p_memoryBegin);
		uintptr_t currentPosition = reinterpret_cast<uintptr_t>(block);
		size_t HeaderSize = sizeof(Header);

		uintptr_t padding = *reinterpret_cast<Header*>(currentPosition - HeaderSize);
		m_currentOffset = currentPosition - padding - HeaderSize - beginPos;
	}

	void StackAllocator::FreeAll(){
		m_currentOffset = 0;
	}

	size_t StackAllocator::GetOffsetMarker()
	{
		return m_currentOffset;
	}

}

