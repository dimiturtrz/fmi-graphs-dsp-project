#include <iostream>
#include <fstream>

#include "helpers/MyStrings.h"
#include "GraphStore.h"

// -------------------------- BIG FOUR HELPERS ------------------------

void GraphStore::clear() {
	delete [] storePath;
}

void GraphStore::copy(const GraphStore& other) {
	dynamicStrcpy(storePath, other.storePath);
}

// --------------------------- OTHER HELPERS --------------------------

bool GraphStore::isUsingGraph() {
	return (graph != NULL);
}
	
bool GraphStore::graphExists(const char* graphId) {
	appendComponentToPath(storePath, graphId);
	std::ifstream graphFile(storePath);
	removeLastComponentFromPath(storePath);
	return graphFile;
}
	
bool GraphStore::nodeExists(const char* nodeId) {
	if(graph == NULL) {
		return false;
	}

	return graph->hasNode(nodeId);
}

bool GraphStore::arcExists(const char* nodeId1, const char* nodeId2) {
	if(graph == NULL) {
		return false;
	}

	return graph->hasArc(nodeId1, nodeId2);
}

// ------------------------------ BIG FOUR ----------------------------

GraphStore::GraphStore(const char* path): storePath(NULL), graph(NULL) {
	dynamicStrcpy(storePath, path);
}

GraphStore::GraphStore(const GraphStore& other) {
	copy(other);
}
GraphStore& GraphStore::operator=(const GraphStore& other) {
	if(this != &other) {
		copy(other);
	}
	return *this;
}
GraphStore::~GraphStore() {
	clear();
}

// --------------------------- GRAPH METHODS ----------------------------

void GraphStore::createGraph(const char* newGraphId, bool directed) {
	return ; // TODO: do
}

void GraphStore::useGraph(const char* existingGraphId) {
	return ; // TODO: do
}

void GraphStore::deleteGraph(const char* existingGraphId) {
	return ; // TODO: do
}

// ---------------------------- NODE METHODS -----------------------------

void GraphStore::createNode(const char* newNodeId) {
	return ; // TODO: do
}
void GraphStore::deleteNode(const char* existingNodeId) {
	return ; // TODO: do
} 

// ---------------------------- ARC METHODS ------------------------------

void GraphStore::createArc(const char* nodeId1, const char* nodeId2, int weight) { 
	return ; // TODO: do
}
void GraphStore::deleteArc(const char* nodeId1, const char* nodeId2) {
	return ; // TODO: do
}

// --------------------------- SEARCH ALGORITMS ---------------------------

void GraphStore::bfs(const char* nodeId1, const char* nodeId2) {
	return ; // TODO: do
}
void GraphStore::dfsShortest(const char* nodeId1, const char* nodeId2) {
	return ; // TODO: do
}
void GraphStore::dfsLongest(const char* nodeId1, const char* nodeId2) {
	return ; // TODO: do
}
void GraphStore::dijkstra(const char* nodeId1, const char* nodeId2) {
	return ; // TODO: do
}



