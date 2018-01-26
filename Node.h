#include <iostream>
#include <fstream>

#include "structures/Pair.h"
#include "structures/Queue.h"
#include "structures/Stack.h"
#include "structures/BinarySearchTree.h"

#ifndef NODE
#define NODE

class EnumeratedNode;
class AlgorithmNode;

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

	void bfsVisit(Queue< Pair<Node*, int> >& queue, BinarySearchTree<AlgorithmNode>& optimalityTable);
	void dfsShortVisit(Stack< Pair<Node*, int> >& stack, BinarySearchTree<AlgorithmNode>& optimalityTable);
	void dfsLongVisit(Stack< Pair<Node*, int> >& stack, BinarySearchTree<AlgorithmNode>& optimalityTable);
	void dijkstraVisit(Queue< Pair<Node*, int> >& queue, BinarySearchTree<AlgorithmNode>& optimalityTable);
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

class AlgorithmNode {
	Node* address;
	Node* parentAddress;
	int cost;

public:
	AlgorithmNode(Node* address);

	bool operator==(const AlgorithmNode& other);
	bool operator!=(const AlgorithmNode& other);
	bool operator<(const AlgorithmNode& other);
	bool operator>(const AlgorithmNode& other);

	int getCost();
    Node* getAddress();
    Node* getParentAddress();
	void changeOptimalReach(int newCost, Node* newParent);
};

#endif
