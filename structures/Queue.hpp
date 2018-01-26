#include <iostream>

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Queue.h"

template<typename T>
Queue<T>::Node::Node(const T& data, Queue::Node* prev): data(data), prev(prev) {}

template<typename T>
void Queue<T>::copy(const Queue& other) {
	clear();

	if(other.front == NULL) {
        front = back = NULL;
        return;
    }

    front = back = new Node(other.front->data);
	for(Node* otherIter = other.front->prev; otherIter != NULL; otherIter = otherIter->prev) {
		back->prev = new Node(otherIter->data);
        back = back->prev;
	}
}

template<typename T>
void Queue<T>::clear() {
    if(front == NULL) {
        return;
    }

	Queue::Node* iter = front->prev;
	while(iter != NULL) {
		delete front;
		front = iter;
		iter = iter->prev;
	}

	front = back = NULL;
}

template<typename T>
Queue<T>::Queue(): front(NULL), back(NULL) {}

template<typename T>
Queue<T>::Queue(const Queue& other): front(NULL), back(NULL) {
	copy(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}

template<typename T>
Queue<T>::~Queue() {
	clear();
}


template<typename T>
bool Queue<T>::isEmpty() {
	return front == NULL;
}

template<typename T>
T& Queue<T>::getFront() {
	if(isEmpty()) {
		throw;
	}
	return front->data;
}

template<typename T>
void Queue<T>::enqueue(const T& data) {
	Queue::Node* newNode = new Node(data);
	if(back != NULL) {
        back->prev = newNode;
	}
	back = newNode;

	if(front == NULL) {
		front = back;
	}
}

template<typename T>
void Queue<T>::dequeue() {
    if(front == NULL) {
        return;
    }

	Queue::Node* oldFront = front;
	front = front->prev;

	if(back == oldFront) {
		back = front = NULL;
	}

	delete oldFront;
}

#endif
