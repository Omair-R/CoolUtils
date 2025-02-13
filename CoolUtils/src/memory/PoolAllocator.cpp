#include "PoolAllocator.h"


co::PoolAllocator::PoolAllocator(const size_t& size, const size_t& chunckSize, const co_align_t& chunkAlignment):
    IAllocator(size) {

    uintptr_t startAddress = reinterpret_cast<uintptr_t>(p_memoryBegin);
    uintptr_t alignedAddress =  Align(startAddress, chunkAlignment);
    m_memorySize -= alignedAddress - startAddress;

    m_chunckSize = Align(chunckSize, chunkAlignment);

    if (m_chunckSize > size)
        throw std::bad_alloc();

    if (m_chunckSize < sizeof(ChunkNode))
        throw std::bad_alloc();

    FreeAll();
}

co::PoolAllocator::~PoolAllocator(){}

void* co::PoolAllocator::Allocate(const size_t& size, const co_align_t& alignment){

    if (size != 0 || alignment != 0)
        log_warn("Size and alignments are ignored in a pool allocator. Allocated predefined chunk size.");

    void* ptrOut = reinterpret_cast<void*>(p_header);

    if (ptrOut == nullptr)
        throw std::bad_alloc();

    p_header = p_header->next;
    return ptrOut;
}

void co::PoolAllocator::Free(void* block){
    if (block == nullptr)
        return;
    
    if (block < p_memoryBegin || 
        reinterpret_cast<uintptr_t>(block) > reinterpret_cast<uintptr_t>(p_memoryBegin) + m_memorySize)
        throw std::bad_alloc();

    ChunkNode* CurrentPtr = reinterpret_cast<ChunkNode*>(block);
    CurrentPtr->next = p_header;
    p_header = CurrentPtr;
}

void co::PoolAllocator::FreeAll(){
    p_header = nullptr;

    size_t beginAddress = reinterpret_cast<size_t>(p_memoryBegin);
    size_t maxChunksNum = m_memorySize / m_chunckSize;
    
    ChunkNode* ptr;
    for (size_t i = 0; i < maxChunksNum; ++i) {
        ChunkNode* ptr = reinterpret_cast<ChunkNode*>(beginAddress + i * m_chunckSize);
        ptr->next = p_header;
        p_header = ptr;
    }

}
