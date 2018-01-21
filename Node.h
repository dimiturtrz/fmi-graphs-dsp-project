#include "structures/BinarySearchTree.h"

#ifndef NODE
#define NODE

class Node {
	BinarySearchTree<Node*> neightbours;
public:
	Node();
};

#endif
