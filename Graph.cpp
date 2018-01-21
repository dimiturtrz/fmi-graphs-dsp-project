#include "helpers/MyStrings.h"
#include "Graph.h"

// ------------------------ BIG FOUR HELPERS ----------------------

void Graph::clear() {}
void Graph::copy(const Graph& other) {
	strcpy(id, other.id);
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
Graph::~Graph() {}

// ------------------------ OTHER METHODS -------------------------

bool Graph::hasNode(const char* nodeId) {
	return true; // TODO do
}

bool Graph::hasArc(const char* nodeId1, const char* nodeId2) {
	return true; // TODO do
}
