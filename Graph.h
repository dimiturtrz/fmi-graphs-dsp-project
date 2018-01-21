#include "structures/TrenarySearchTree.h"

#include "Node.h"

#ifndef GRAPH
#define GRAPH

class Graph {
	TrenarySearchTree<Node> nodes;
	char id[50];
	bool directed;

	void clear();
	void copy(const Graph& other);
public:
	Graph(const char* graphId = "");
	Graph(const Graph& other);
	Graph& operator=(const Graph& other);
	~Graph();

	void readFromFile(const char* path);
	void writeToFile(const char* path);

	bool hasNode(const char* nodeId);
	bool hasArc(const char* nodeId1, const char* nodeId2);

	const char* getId();

	void addNode(const char* nodeId);
	void removeNode(const char* nodeId);
};

#endif
