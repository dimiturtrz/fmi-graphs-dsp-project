#include "structures/TrenarySearchTree.h"

#ifndef GRAPH
#define GRAPH

class Graph {
	char id[50];
	bool directed;

	void clear();
	void copy(const Graph& other);
	void readFromFile(const char* path);

public:
	Graph(char* storePath, const char* graphId);
	Graph(const Graph& other);
	Graph& operator=(const Graph& other);
	~Graph();

	bool hasNode(const char* nodeId);
	bool hasArc(const char* nodeId1, const char* nodeId2);
};

#endif
