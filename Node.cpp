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
bool Node::Arc::operator!=(const Arc& other) {
	return !(*this == other);
}

// ------------------------ NEIGHBOUR BST -----------------------------

Node::Arc* Node::NeighboursBST::getNeighbour(Node* neighbour) {
	return getElement(Arc(neighbour, 0));
}

void Node::NeighboursBST::removeNeighbour(Node* neighbour) {
	Arc* arc = getElement(Arc(neighbour, 0));
	if(arc != NULL) {
		remove(*arc);
	}
}

// ---------------------------- NODE ----------------------------------
bool Node::hasNeighbour(Node* neighbour) {
	return neighbours.getNeighbour(neighbour) != NULL;
}

void Node::addNeighbour(Node* neighbour, int weight) {
	neighbours.add(Arc(neighbour, weight));
}

void Node::removeNeighbour(Node* node) {
	neighbours.removeNeighbour(node);
}
