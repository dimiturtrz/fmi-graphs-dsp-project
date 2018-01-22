#include "structures/BinarySearchTree.h"

#ifndef NODE
#define NODE

class Node {
	struct Arc {
		int weight;
		Node* end;
	public:
		Arc(Node* end, int weight);
		bool operator>(const Arc& other);
		bool operator<(const Arc& other);
		bool operator==(const Arc& other);
	};

	class NeighboursBST: BinarySearchTree<Node::Arc> {
	public:
		Arc* getNeighbour(Node* neightbour);
	};

	NeighboursBST neighbours;
public:
	bool hasNeighbour(Node* neighbour);
};

#endif
