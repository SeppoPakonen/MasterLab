#ifndef _Tooling_CuteAtomic_h_
#define _Tooling_CuteAtomic_h_

using CuteAtomic = AudioAtomic;

inline int CuteAtomicGet(CuteAtomic* atomic_value) {
	return AtomicGet(atomic_value);
}

inline void CuteAtomicSet(CuteAtomic* atomic_value, int next_value) {
	AtomicSet(atomic_value, next_value);
}

inline int CuteAtomicCompareAndSwap(CuteAtomic* atomic_value, int old_value, int new_value) {
	return AtomicCompareAndSwap(atomic_value, old_value, new_value);
}

inline int CuteAtomicTestAndSet(CuteAtomic* atomic_value) {
	return AtomicTestAndSet(atomic_value);
}

inline int CuteAtomicAdd(CuteAtomic* atomic_value, int add_value) {
	return AtomicAdd(atomic_value, add_value);
}

inline int CuteAtomicIncrement(CuteAtomic* atomic_value) {
	return AtomicIncrement(atomic_value);
}

inline int CuteAtomicDecrement(CuteAtomic* atomic_value) {
	return AtomicDecrement(atomic_value);
}

inline int CuteAtomicTestAndZero(CuteAtomic* atomic_value) {
	return AtomicTestAndZero(atomic_value);
}

#endif
