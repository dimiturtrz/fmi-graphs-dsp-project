#include <iostream>
#include <fstream>

#include "structures/BinarySearchTree.h"
#include "helpers/MyStrings.h"
#include "Graph.h"
#include "Node.h"

// ------------------------ BIG FOUR HELPERS ----------------------

void Graph::clear() {}

void Graph::copy(const Graph& other) {
	strcpy(id, other.id);
	directed = other.directed;
	nodes = other.nodes;
}

// --------------------------- BIG FOUR ---------------------------

Graph::Graph(const char* graphId) {
	strcpy(id, graphId);
}
Graph::Graph(const Graph& other) {
	copy(other);
}
Graph& Graph::operator=(const Graph& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}
Graph::~Graph() {
	clear();
}

// ------------------------- FILE OPERATIONS ----------------------

void Graph::readFromFile(const char* path) {
	if(path == NULL) {
		return;
	}

	clear();

	char buff[1024];
	char word[51];
	std::ifstream inputGraphFile(path);

	inputGraphFile>> directed;
	inputGraphFile.getline(buff, 1023);
	inputGraphFile.getline(buff, 1023);

	while(inputGraphFile.peek() != '\n' && inputGraphFile.getline(buff, 1023)) {
		strcpy(word, buff, ' ');
		nodes.add(word, Node());
	}

	inputGraphFile.close();
}

void Graph::writeToFile(const char* path) {
	if(path == NULL) {
		return;
	}

	char buff[51];

	std::ofstream outputGraphFile(path);

	outputGraphFile<< directed<< std::endl<< std::endl;

	int index = 0;
	BinarySearchTree<EnumeratedNode> indexedNodes;
	for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
		iter.getWord(buff);
		outputGraphFile<< buff<< std::endl;
		indexedNodes.add(EnumeratedNode(&(*iter), index++));
	}

	outputGraphFile<< std::endl;

	for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
		(*iter).writeToFile(outputGraphFile, indexedNodes);
	}

	outputGraphFile.close();
}

// ------------------------ OTHER METHODS -------------------------

bool Graph::hasNode(const char* nodeId) {
	return nodes.getElement(nodeId) != NULL;
}

bool Graph::hasArc(const char* nodeId1, const char* nodeId2) {
	Node* node1 = nodes.getElement(nodeId1);
	Node* node2 = nodes.getElement(nodeId2);

	if(node1 == NULL || node2 == NULL) {
		return false;
	}

	return node1->hasNeighbour(node2);
}

// --------------------------- GETTERS -----------------------------

const char* Graph::getId() {
	return id;
}

// ------------------------- NODE METHODS --------------------------

void Graph::addNode(const char* nodeId) {
	nodes.add(nodeId, Node());
}

void Graph::removeNode(const char* nodeId) {
	Node* oldNode = nodes.getElement(nodeId);
	nodes.remove(nodeId);
	for(TrenarySearchTree<Node>::Iterator iter = nodes.begin(); !iter.isFinished(); ++iter) {
		(*iter).removeNeighbour(oldNode);
	}
}

// -------------------------- ARC METHODS --------------------------

void Graph::addArc(const char* nodeId1, const char* nodeId2, int weight) {
	Node* node1 = nodes.getElement(nodeId1);
	Node* node2 = nodes.getElement(nodeId2);

	if(node1 != NULL && node2 != NULL) {
		node1->addNeighbour(node2, weight);
		if(!directed) {
			node2->addNeighbour(node1, weight);
		}
	}
}

void Graph::removeArc(const char* nodeId1, const char* nodeId2) {
	Node* node1 = nodes.getElement(nodeId1);
	Node* node2 = nodes.getElement(nodeId2);

	if(node1 != NULL && node2 != NULL) {
		node1->removeNeighbour(node2);
	}
}

