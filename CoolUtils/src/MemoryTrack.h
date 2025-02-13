#pragma once
#include "patterns/Singlton.h"
#include <vector>
#include <unordered_map>
#include <fmt/core.h>


namespace co {

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	class MemoryTrack : public SafeAbstractSinglton<MemoryTrack<MemoryTagEnum>>
	{
	public:
		void Initialize(MemoryTagEnum first, MemoryTagEnum last);

		void Initialize(std::vector<MemoryTagEnum> enumList);

		template <class C, MemoryTagEnum tag, typename ...Args>
		C* AllocateMemory(Args&&...args);

		template <class C, size_t size, MemoryTagEnum tag, typename ...Args>
		C* AllocateMemory(Args&&...args);

		template <class C, MemoryTagEnum tag>
		void FreeMemory(C* block, size_t size = 0);

		uint64_t GetTotalMemory();

		uint64_t GetTaggedMemory(MemoryTagEnum tag);

		std::string GetSummary(bool verbose = false);

		std::string GetTagSummary(MemoryTagEnum tag);


	private:

		std::string FormatMemory(uint64_t size);

		uint64_t totalMemorySize{ 0 };
		std::unordered_map<MemoryTagEnum, uint32_t> tagMemorySize;
	};
}

#include "MemoryTrack_T.h"