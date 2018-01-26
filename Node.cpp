#include "Node.h"

#include "structures/Pair.h"
#include "structures/Queue.h"

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

// ------------------------- ALGORITHM NODE ---------------------------

AlgorithmNode::AlgorithmNode(Node* address): cost(-1), address(address), parentAddress(NULL) {}

bool AlgorithmNode::operator==(const AlgorithmNode& other) {
    return address == other.address;
}
bool AlgorithmNode::operator!=(const AlgorithmNode& other) {
    return *this != other;
}
bool AlgorithmNode::operator<(const AlgorithmNode& other) {
    return address < other.address;
}
bool AlgorithmNode::operator>(const AlgorithmNode& other) {
    return address > other.address;
}

int AlgorithmNode::getCost() {
    return cost;
}

Node* AlgorithmNode::getAddress() {
    return address;
}

Node* AlgorithmNode::getParentAddress() {
    return parentAddress;
}

void AlgorithmNode::changeOptimalReach(int newCost, Node* newParent) {
    cost = newCost;
    parentAddress = newParent;
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
	for(NeighboursBST::Iterator iter = neighbours.begin(); !iter.isFinished(); ++iter) {
		Arc arcToWrite = *iter;
		int endNodeIndex = indexedNodes.getElement(EnumeratedNode(arcToWrite.end, -1))->getIndex();
		outputGraphFile<< endNodeIndex<< " "<< arcToWrite.weight<< ", ";
	}
}

// ---------------------------- NODE ----------------------------------
bool Node::hasNeighbour(Node* neighbour) {
	return neighbours.getNeighbour(neighbour) != NULL;
}

void Node::addNeighbour(Node* neighbour, int weight) {
    if(neighbours.getNeighbour(neighbour) == NULL) {
        neighbours.add(Arc(neighbour, weight));
    }
}

void Node::removeNeighbour(Node* node) {
	neighbours.removeNeighbour(node);
}

// --------------------------- ALGORITHMS ----------------------------

void Node::bfsVisit(Queue< Pair<Node*, int> >& queue, BinarySearchTree<AlgorithmNode>& optimalityTable, int depth) {
    for(NeighboursBST::Iterator iter = neighbours.begin(); !iter.isFinished(); ++iter) {
        Node* endpoint = (*iter).end;
        AlgorithmNode& algorithmNode = *(optimalityTable.getElement(AlgorithmNode(endpoint)));
        if(algorithmNode.getCost() == -1) {
            algorithmNode.changeOptimalReach(depth + 1, this);
            queue.enqueue(Pair<Node*, int>(endpoint, depth + 1));
        }
    }
}
