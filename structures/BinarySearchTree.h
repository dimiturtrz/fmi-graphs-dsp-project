#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

template <class T>
class BinarySearchTree {
	struct Node {
		Node* left;
		Node* right;
		T data;

		public:
			Node(T data, Node* left = NULL, Node* right = NULL);
	} * root;

	void copy(const BinarySearchTree& other);
	void copySubtree(Node*& currRoot, Node* otherCurrRoot);

	void clear();
	void clearSubtree(Node*& currRoot);

	void add(const T& data, Node*& currRoot);
	void remove(const T& data, Node*& currRoot);

	T* getElement(const T& data, Node* currRoot);
	void printSubtree(Node* currRoot);

	Node* removeNode(Node* node);
	T getAndRemoveMin(Node* node, Node*& parent);
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	BinarySearchTree& operator=(const BinarySearchTree& other);
	~BinarySearchTree();

	void add(const T& data);
	void remove(const T& data);

	T* getElement(const T& data);

	void print();
};

#include "BinarySearchTree.hpp"

#endif
