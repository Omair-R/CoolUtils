#pragma once

namespace co {
	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	void MemoryTrack<MemoryTagEnum>::Initialize(MemoryTagEnum first, MemoryTagEnum last) {
		for (MemoryTagEnum e = first; e <= last; e = static_cast<MemoryTagEnum>(e + 1))
			tagMemorySize[e] = 0;
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	void MemoryTrack<MemoryTagEnum>::Initialize(std::vector<MemoryTagEnum> enumList) {
		for (MemoryTagEnum e : enumList)
			tagMemorySize[e] = 0;
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	template <class C, MemoryTagEnum tag, typename ...Args> 
	C* MemoryTrack<MemoryTagEnum>::AllocateMemory(Args&&...args) {

		//std::lock_guard<std::mutex> lock(_mutex);

		size_t size = sizeof(C);

		totalMemorySize += size;
		tagMemorySize[tag] += size;

		C* block = new C(args...);
		return block;
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	template <class C, size_t size, MemoryTagEnum tag, typename ...Args>
	C* MemoryTrack<MemoryTagEnum>::AllocateMemory(Args&&...args) {

		//std::lock_guard<std::mutex> lock(_mutex);

		size_t blockSize = sizeof(C) * size;

		totalMemorySize += blockSize;
		tagMemorySize[tag] += blockSize;

		C* block = new C[size](args...);
		return block;
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	template <class C, MemoryTagEnum tag>
	void MemoryTrack<MemoryTagEnum>::FreeMemory(C* block, size_t size) {

		//std::lock_guard<std::mutex> lock(_mutex);

		size_t blockSize;

		if (size != 0) {
			blockSize = sizeof(C) * size;
			delete[] block;
		}
		else {
			blockSize = sizeof(C);
			delete block;
		}

		totalMemorySize -= blockSize;
		tagMemorySize[tag] -= blockSize;
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	uint64_t MemoryTrack<MemoryTagEnum>::GetTotalMemory() {
		return totalMemorySize;
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	uint64_t MemoryTrack<MemoryTagEnum>::GetTaggedMemory(MemoryTagEnum tag) {
		return tagMemorySize[tag];
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	std::string MemoryTrack<MemoryTagEnum>::GetSummary(bool verbose) {
		std::string outputString = fmt::format("Total memory usage: {}", FormatMemory(totalMemorySize));
		if (verbose) {
			outputString += "\n";
			for (const auto& [key, value] : tagMemorySize) {
				outputString += fmt::format("\t tag [{}]: {}\n", (int)key, FormatMemory(value));
			}
		}
		return outputString;
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	std::string MemoryTrack<MemoryTagEnum>::GetTagSummary(MemoryTagEnum tag) {
		return fmt::format("Tag memory usage: {}", FormatMemory(tagMemorySize[tag]));
	}

	template <typename MemoryTagEnum> requires std::is_enum_v<MemoryTagEnum>
	std::string MemoryTrack<MemoryTagEnum>::FormatMemory(uint64_t size) {
		std::string unit = "XiB";
		std::string stringOut;
		uint64_t kib = 1024;
		uint64_t mib = 1024 * 1024;
		uint64_t gib = 1024 * 1024 * 1024;
		if (size > gib) {
			unit[0] = 'G';
			stringOut = fmt::format("{} {}", (float)size / gib, unit);
		}
		else if (size > mib) {
			unit[0] = 'M';
			stringOut = fmt::format("{} {}", (float)size / mib, unit);
		}
		else if (size > kib) {
			unit[0] = 'K';
			stringOut = fmt::format("{} {}", (float)size / kib, unit);
		}
		else {
			unit = "bytes";
			stringOut = fmt::format("{} {}", (float)size, unit);
		}
		return stringOut;
	}


}