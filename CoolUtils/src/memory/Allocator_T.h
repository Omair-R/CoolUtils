#pragma once

namespace co {

	inline uintptr_t Align(const uintptr_t& ptr, const co_align_t& align) {
		if ((align & (align - 1)) != 0)
			return 0;

		uintptr_t ptrOut = ptr;

		//ptrOut += ptrOut % align;
		uintptr_t m = ptrOut & (align - 1);

		if (m != 0)
			ptrOut += align - m;

		return ptrOut;
	}

	template <typename T = void>
	inline T* placePointer(const uintptr_t& position) {
		return reinterpret_cast<T*> (position);
	}
}
