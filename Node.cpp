#include "Node.h"

// ---------------------------- ARC -----------------------------------
Node::Arc::Arc(Node* end, int weight): end(end), weight(weight) {}

bool Node::Arc::operator>(const Arc& other) {
	return end > other.end;
}
bool Node::Arc::operator<(const Arc& other) {
	return end < other.end;
}
bool Node::Arc::operator==(const Arc& other) {
	return end == other.end;
}

// ----------------------- NEIGHBOUR BST ------------------------------

Node::Arc* Node::NeighboursBST::getNeighbour(Node* neighbour) {
	return getElement(Arc(neighbour, 0));
}

// ---------------------------- NODE ----------------------------------
bool Node::hasNeighbour(Node* neighbour) {
	return neighbours.getNeighbour(neighbour) != NULL;
}
