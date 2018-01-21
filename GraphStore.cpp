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
