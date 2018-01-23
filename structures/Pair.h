#ifndef PAIR
#define PAIR

template<class T1, class T2>
struct Pair {
	T1 first;
	T2 second;

public:
	Pair(T1 first, T2 second);
};

#endif
