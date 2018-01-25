#include "Stack.hpp"

#ifndef TRENARY_SEARCH_TREE_H
#define TRENARY_SEARCH_TREE_H

template <class T>
class TrenarySearchTree {
	struct TSTNode {
		TSTNode* hi;
		TSTNode* lo;
		TSTNode* equal;

		char character;
		T* data;

		void clear();
		void copy(const TSTNode& other);

	public:
		TSTNode(char character, T* data = NULL);
		TSTNode(const TSTNode& other);
		TSTNode& operator=(const TSTNode& other);
		~TSTNode();
	} * root;

	void clear();
	void clearSubtree(TSTNode*& currRoot);

	void copy(const TrenarySearchTree& other);
	void copySubtree(TSTNode*& currRoot, TSTNode* otherCurrRoot);

	void add(const char* key, const T& data, TSTNode*& currRoot);
	void remove(const char* key, TSTNode*& currRoot);

	T* getElement(const char* key, TSTNode* currRoot);
	void printSubtree(TSTNode* currRoot, char* accumWord, int accumWordIndex);
public:
	class Iterator {
        const TSTNode* root;
        TSTNode* lastPop;
        TSTNode* lastVisited;
		Stack<TSTNode*> iterationStack;
	public:
		Iterator(TSTNode* root);
		void sink();
		void emerge();
		T& operator*();
		Iterator& operator++();
		Iterator& operator++(int);
		void getWord(char buffer[]);
		bool isFinished();
	};

	TrenarySearchTree();
	TrenarySearchTree(const TrenarySearchTree& other);
	TrenarySearchTree& operator=(const TrenarySearchTree& other);
	~TrenarySearchTree();

	Iterator begin();

	void add(const char* key, const T& data);
	void remove(const char* key);

	T* getElement(const char* key);

	void print();
};

#include "TrenarySearchTree.hpp"

#endif
