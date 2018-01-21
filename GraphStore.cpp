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

bool GraphStore::createGraph(const char* newGraphId, bool directed) {
	return true; // TODO: do
}

bool GraphStore::useGraph(const char* existingGraphId) {
	return true; // TODO: do
}

bool GraphStore::deleteGraph(const char* existingGraphId) {
	return true; // TODO: do
}

// ---------------------------- NODE METHODS -----------------------------

bool GraphStore::createNode(const char* newNodeId) {
	return true; // TODO: do
}
bool GraphStore::deleteNode(const char* existingNodeId) {
	return true; // TODO: do
} 

// ---------------------------- ARC METHODS ------------------------------

bool GraphStore::createArc(const char* nodeId1, const char* nodeId2, int weight) { 
	return true; // TODO: do
}
bool GraphStore::deleteArc(const char* nodeId1, const char* nodeId2) {
	return true; // TODO: do
}



