#ifndef VECTOR
#define VECTOR

template<class T>
class Vector {
	T* data;
	int size;
	int capacity;

	void copy(const Vector& other);
	void clear();

	void expand();
	void shrink();

public:
	Vector(int capacity = 2);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	void add(T newElement);
	void remove(T element);

	T& getElement(int index);
	T& operator[](int index);

	int getSize();
};

#include "Vector.hpp"

#endif
