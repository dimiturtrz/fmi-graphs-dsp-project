#include "Stack.hpp"

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

template <class T>
class BinarySearchTree {
	struct BSTNode {
		BSTNode* left;
		BSTNode* right;
		T data;
	public:
		BSTNode(T data, BSTNode* left = NULL, BSTNode* right = NULL);
	} * root;

	void copy(const BinarySearchTree& other);
	void copySubtree(BSTNode*& currRoot, BSTNode* otherCurrRoot);

	void clear();
	void clearSubtree(BSTNode*& currRoot);

	void add(const T& data, BSTNode*& currRoot);
	void remove(const T& data, BSTNode*& currRoot);

	T* getElement(const T& data, BSTNode* currRoot);
	void printSubtree(BSTNode* currRoot);

	BSTNode* removeBSTNode(BSTNode* node);
	T getAndRemoveMin(BSTNode* node, BSTNode*& parent);
public:
	class Iterator {
		Stack<BSTNode*> iterationStack;
	public:
		Iterator(BSTNode* root);
		T& operator*();
		Iterator& operator++();
		Iterator& operator++(int);
		bool isFinished();
	};

	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	BinarySearchTree& operator=(const BinarySearchTree& other);
	~BinarySearchTree();

	Iterator begin();

	void add(const T& data);
	void remove(const T& data);

	T* getElement(const T& data);

	void print();
};

#include "BinarySearchTree.hpp"

#endif
