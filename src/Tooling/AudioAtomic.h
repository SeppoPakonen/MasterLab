#ifndef _Tooling_AudioAtomic_h_
#define _Tooling_AudioAtomic_h_

struct AudioAtomic {
	volatile int value = 0;
};

inline int AtomicGet(AudioAtomic* atomic_value) {
	return atomic_value->value;
}

inline void AtomicSet(AudioAtomic* atomic_value, int next_value) {
	atomic_value->value = next_value;
}

inline int AtomicCompareAndSwap(AudioAtomic* atomic_value, int old_value, int new_value) {
	if(atomic_value->value == old_value) {
		atomic_value->value = new_value;
		return 1;
	}
	return 0;
}

inline int AtomicTestAndSet(AudioAtomic* atomic_value) {
	return AtomicCompareAndSwap(atomic_value, 0, 1);
}

inline int AtomicAdd(AudioAtomic* atomic_value, int add_value) {
	int old_value;
	int new_value;
	do {
		old_value = AtomicGet(atomic_value);
		new_value = old_value + add_value;
	}
	while(!AtomicCompareAndSwap(atomic_value, old_value, new_value));
	return new_value;
}

inline int AtomicIncrement(AudioAtomic* atomic_value) {
	return AtomicAdd(atomic_value, 1);
}

inline int AtomicDecrement(AudioAtomic* atomic_value) {
	return AtomicAdd(atomic_value, -1);
}

inline int AtomicTestAndZero(AudioAtomic* atomic_value) {
	int old_value;
	do {
		old_value = AtomicGet(atomic_value);
	}
	while(old_value && !AtomicCompareAndSwap(atomic_value, old_value, 0));
	return old_value;
}

#endif
