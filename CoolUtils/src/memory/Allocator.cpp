#include "Allocator.h"

namespace co {

	IAllocator::IAllocator(const size_t& size){
		m_memorySize = size;
		p_memoryBegin = ::operator new(m_memorySize);
	}

	IAllocator::~IAllocator()
	{
		::operator delete(p_memoryBegin);
		p_memoryBegin = nullptr;
	}

}