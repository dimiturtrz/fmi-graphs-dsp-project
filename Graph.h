#include "structures/TrenarySearchTree.h"

#ifndef GRAPH
#define GRAPH

class Graph {
	char id[50];
	bool directed;

	void clear();
	void copy(const Graph& other);
public:
	Graph(char* storePath = NULL, const char* graphId = "");
	Graph(const Graph& other);
	Graph& operator=(const Graph& other);
	~Graph();

	void readFromFile(const char* path);
	void writeToFile(const char* path);

	bool hasNode(const char* nodeId);
	bool hasArc(const char* nodeId1, const char* nodeId2);

	const char* getId();
};

#endif