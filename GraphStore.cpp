#include "helpers/MyStrings.h"
#include "GraphStore.h"

void GraphStore::clear() {
	delete [] storePath;
	delete [] usedGraphId;
}

void GraphStore::copy(const GraphStore& other) {
	dynamicStrcpy(storePath, other.storePath);
	dynamicStrcpy(usedGraphId, other.usedGraphId);
}

GraphStore::GraphStore(const char* path): storePath(NULL), usedGraphId(NULL) {
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
