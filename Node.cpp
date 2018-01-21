#include "Node.h"

bool Node::hasNeighbour(Node* neighbour) {
	return (neighbours.getElement(neighbour) != NULL);
}
