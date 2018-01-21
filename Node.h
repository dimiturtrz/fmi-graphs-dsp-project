#include "structures/BinarySearchTree.h"

#ifndef NODE
#define NODE

class Node {
	BinarySearchTree<Node*> neighbours;
public:

	bool hasNeighbour(Node* neighbour);
};

#endif
