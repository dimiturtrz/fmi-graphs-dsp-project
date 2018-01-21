#include "helpers/MyStrings.h"
#include "GraphStore.h"

// -------------------------- BIG FOUR HELPERS ------------------------

void GraphStore::clear() {
	delete [] storePath;
}

void GraphStore::copy(const GraphStore& other) {
	dynamicStrcpy(storePath, other.storePath);
	strcpy(usedGraphId, other.usedGraphId);
}

// --------------------------- OTHER HELPERS --------------------------

bool GraphStore::isUsingGraph() {
	return (*usedGraphId != '\0');
}
	
bool GraphStore::graphExists(const char* graphId) {
	return true; // TODO do
}
	
bool GraphStore::nodeExists(const char* nodeId) {
	return true; // TODO do
}

bool GraphStore::arcExists(const char* nodeId1, const char* nodeId2) {
	return true; // TODO do
}

// ------------------------------ BIG FOUR ----------------------------

GraphStore::GraphStore(const char* path): storePath(NULL) {
	dynamicStrcpy(storePath, path);
	usedGraphId[0] = '\0';
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



