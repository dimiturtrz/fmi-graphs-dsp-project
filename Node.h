#include <iostream>
#include <fstream>

#include "structures/BinarySearchTree.h"

#ifndef NODE
#define NODE

class EnumeratedNode;

class Node {
	struct Arc {
		int weight;
		Node* end;
	public:
		Arc(Node* end, int weight);
		bool operator>(const Arc& other);
		bool operator<(const Arc& other);
		bool operator==(const Arc& other);
		bool operator!=(const Arc& other);
	};

	class NeighboursBST: public BinarySearchTree<Node::Arc> {
	public:
		Arc* getNeighbour(Node* neightbour);
		void removeNeighbour(Node* neighbour);
	};

	NeighboursBST neighbours;
public:
	bool hasNeighbour(Node* neighbour);
	void addNeighbour(Node* node, int weight = 1);
	void removeNeighbour(Node* node);

	void writeToFile(std::ofstream& outputGraphFile, BinarySearchTree<EnumeratedNode> indexedNodes);
};

class EnumeratedNode {
	Node* nodeAddress;
	int index;

public:
	EnumeratedNode(Node* nodeAddress, int index);

	bool operator==(const EnumeratedNode& other);
	bool operator<(const EnumeratedNode& other);
	bool operator>(const EnumeratedNode& other);

	int getIndex();
};

#endif
