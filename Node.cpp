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

// ------------------------ ENUMERATED NODE ----------------------------

EnumeratedNode::EnumeratedNode(Node* nodeAddress, int index): nodeAddress(nodeAddress), index(index) {}

bool EnumeratedNode::operator==(const EnumeratedNode& other) {
	return nodeAddress == other.nodeAddress;
}

bool EnumeratedNode::operator<(const EnumeratedNode& other) {
	return nodeAddress < other.nodeAddress;
}

bool EnumeratedNode::operator>(const EnumeratedNode& other) {
	return nodeAddress > other.nodeAddress;
}

int EnumeratedNode::getIndex() {
	return index;
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

// -------------------------- FILE WRITE ------------------------------

void Node::writeToFile(std::ofstream& outputGraphFile, BinarySearchTree<EnumeratedNode> indexedNodes) {
	bool first = true;
	for(NeighboursBST::Iterator iter = neighbours.begin(); !iter.isFinished(); ++iter) {
		if(!first) {
			outputGraphFile<< ", ";
		}
		first = false;

		Arc arcToWrite = *iter;
		int endNodeIndex = indexedNodes.getElement(EnumeratedNode(arcToWrite.end, -1))->getIndex();
		outputGraphFile<< endNodeIndex<< " "<< arcToWrite.weight;
	}
	outputGraphFile<< std::endl;
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
