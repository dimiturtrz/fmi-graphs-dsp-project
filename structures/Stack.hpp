#include <iostream>

#ifndef STACK_HPP
#define STACK_HPP

#include "Stack.h"

template<typename T>
Stack<T>::Node::Node(const T& data, Stack::Node* next): data(data), next(next) {}

template<typename T>
void Stack<T>::copy(const Stack& other) {
	clear();
	for(Stack::Node *thisIter = top, *otherIter = other.top;
			otherIter != NULL; otherIter = otherIter->next) {
		thisIter = new Node(otherIter->data);
	}
}

template<typename T>
void Stack<T>::clear() {
    if(top == NULL) {
        return;
    }

	Stack::Node* iter = top->next;
	while(iter != NULL) {
		delete top;
		top = iter;
		iter = iter->next;
	}
	delete top;
	top = NULL;
}

template<typename T>
Stack<T>::Stack(): top(NULL) {}

template<typename T>
Stack<T>::Stack(const Stack& other) {
	copy(other);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}

template<typename T>
Stack<T>::~Stack() {
	clear();
}


template<typename T>
bool Stack<T>::isEmpty() {
	return top == NULL;
}

template<typename T>
T& Stack<T>::getTop() {
	if(isEmpty()) {
		throw;
	}
	return top->data;
}

template<typename T>
void Stack<T>::push(const T& data) {
	Stack::Node* newNode = new Node(data);
	newNode->next = top;
	top = newNode;
}

template<typename T>
void Stack<T>::pop() {
    if(top == NULL) {
        return;
    }

	Stack::Node* oldTop = top;
	top = top->next;
	delete oldTop;
}

#endif
