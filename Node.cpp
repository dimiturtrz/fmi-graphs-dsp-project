#include "Node.h"

// ---------------------------- ARC -----------------------------------
Node::Arc::Arc(Node* end, int weight): end(end), weight(weight) {}


// ---------------------------- NODE ----------------------------------
bool Node::hasNeighbour(Node* neighbour) {
	return true;//(neighbours.getElement(neighbour) != NULL);
}
