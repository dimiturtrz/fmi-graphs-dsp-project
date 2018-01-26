#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class Queue {
	struct Node {
		T data;
		Node* prev;

		Node(const T& data, Node* prev = NULL);
	} * back, * front;

	void copy(const Queue& other);
	void clear();
public:
	Queue();
	Queue(const Queue& other);
	Queue& operator=(const Queue& other);
	~Queue();

	bool isEmpty();
	T& getFront();
	void enqueue(const T& data);
	void dequeue();
};

#include "Queue.hpp"

#endif
