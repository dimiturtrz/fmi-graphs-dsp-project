

// -------------------------- BIG FOUR HELPERS ------------------------------
template<typename T>
void Vector<T>::copy(const Vector& other) {
	clear();
	capacity = other.capacty;
	data = new T[capacity];
	for(size = 0; size < other.size; ++size) {
		data[size] = other.data[size];
	}
}

template<typename T>
void Vector<T>::clear() {
	size = capacity = 0;
	delete [] data;
	data = NULL;
}


// ----------------------------- BIG FOUR -----------------------------------
template<typename T>
Vector<T>::Vector(int capacity): size(0), capacity(capacity), data(NULL) {
	data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector& other) {
	copy(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector() {
	clear();
}

// -------------------------- OPERATION HELPERS -----------------------------

template<typename T>
void Vector<T>::expand() {
	T* newData = new T[capacity*2];
	for(int i = 0; i < size; ++i) {
		newData[i] = data[i];
	}
	capacity *= 2;

	delete [] data;
	data = newData;
}

template<typename T>
void Vector<T>::shrink() {
	T* newData = new T[capacity/2];
	for(int i = 0; i < size; ++i) {
		newData[i] = data[i];
	}
	capacity /= 2;

	delete [] data;
	data = newData;
}

// ----------------------------- OPERATIONS ----------------------------------

template<typename T>
void Vector<T>::add(T newElement) {
	if(size >= capacity) {
		expand();
	}
	data[size++] = newElement;
}

// O(N)!!!
template<typename T>
void Vector<T>::remove(T element) {
	int i = 0;
	for(; i < size && data[i] != element; ++i);
	if(i + 1 <= size) {
		for(int l = i + 1; l < size; ++l) {
			data[l - 1] = data[l];
		}
		size -= 1;
		if(size <= capacity/2) {
			shrink();
		}
	}
}

// ---------------------------- GET ELEMENT -----------------------------------

template<typename T>
T& Vector<T>::getElement(int index) {
	return data[index];
}

template<typename T>
T& Vector<T>::operator[](int index) {
	return data[index];
}

// ----------------------------- GETTERS --------------------------------------

template<typename T>
int Vector<T>::getSize() {
	return size;
}
