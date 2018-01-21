#ifndef TRENARY_SEARCH_TREE_H
#define TRENARY_SEARCH_TREE_H

template <class T>
class TrenarySearchTree {
	struct Node {
		Node* hi;
		Node* lo;
		Node* equal;

		char character;
		T* data;

	public:
		Node(char character, T* data = NULL);
	} * root;

	void clear();
	void clearSubtree(Node*& currRoot);

	void copy(const TrenarySearchTree& other);
	void copySubtree(Node*& currRoot, Node* otherCurrRoot);

	void add(const char* key, const T& data, Node*& currRoot);
	void remove(const char* key, Node*& currRoot);

	T* getElement(const char* key, Node* currRoot);
	void printSubtree(Node* currRoot, char* accumWord, int accumWordIndex);
public:
	TrenarySearchTree();
	TrenarySearchTree(const TrenarySearchTree& other);
	TrenarySearchTree& operator=(const TrenarySearchTree& other);
	~TrenarySearchTree();

	void add(const char* key, const T& data);
	void remove(const char* key);

	T* getElement(const char* key);

	void print();
};

#include "TrenarySearchTree.hpp"

#endif
