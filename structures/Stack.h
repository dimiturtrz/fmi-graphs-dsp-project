#ifndef STACK_H
#define STACK_H

template<class T>
class Stack {
	struct Node {
		T data;
		Node* next;

		Node(const T& data, Node* next = NULL);
	} * top;

	void copy(const Stack& other);
	void clear();
public:
	Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);
	~Stack();

	bool isEmpty();
	T& getTop();
	void push(const T& data);
	void pop();
};

#endif
