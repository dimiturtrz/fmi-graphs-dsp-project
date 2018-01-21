#include <iostream>
#include <fstream>

#include <stdio.h> // only for file removal

#include "helpers/MyStrings.h"
#include "GraphStore.h"

// -------------------------- BIG FOUR HELPERS ------------------------

void GraphStore::clear() {
	delete [] storePath;
}

void GraphStore::copy(const GraphStore& other) {
	dynamicStrcpy(storePath, other.storePath);
}

void GraphStore::makeGraph(const char* id, bool directed) {
    appendComponentToPath(storePath, id);
	std::ofstream outfile(storePath);
	outfile<< (directed ? 1 : 0)<< std::endl;
	outfile.close();
	removeLastComponentFromPath(storePath);
}

void GraphStore::openGraph(const char* id) {
	appendComponentToPath(storePath, id);
	graph = new Graph(id);
	graph->readFromFile(storePath);
	removeLastComponentFromPath(storePath);
}

void GraphStore::closeGraph() {
	if(graph == NULL) {
		return;
	}

	appendComponentToPath(storePath, graph->getId());
	graph->writeToFile(storePath);
	removeLastComponentFromPath(storePath);

	delete graph;
	graph = NULL;
}

// --------------------------- OTHER HELPERS --------------------------

bool GraphStore::isUsingGraph() {
	return (graph != NULL);
}

bool GraphStore::graphExists(const char* graphId) {
	appendComponentToPath(storePath, graphId);
	std::ifstream graphFile(storePath);
	bool fileOpened = graphFile;
	graphFile.close();
	removeLastComponentFromPath(storePath);
	return fileOpened;
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
    makeGraph(newGraphId, directed);
	useGraph(newGraphId);
}

void GraphStore::useGraph(const char* existingGraphId) {
	closeGraph();
	openGraph(existingGraphId);
}

void GraphStore::deleteGraph(const char* existingGraphId) {
    if(strcmp(existingGraphId, graph->getId()) == 0) {
        closeGraph();
    }

	appendComponentToPath(storePath, existingGraphId);
	remove(storePath);
	removeLastComponentFromPath(storePath);
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



