#include "structures/BinarySearchTree.h"

#ifndef NODE
#define NODE

class Node {
	struct Arc {
		int weight;
		Node* end;
	public:
		Arc(Node* end, int weight);
	};

	BinarySearchTree<Arc> neighbours;
public:
	bool hasNeighbour(Node* neighbour);
};

#endif
