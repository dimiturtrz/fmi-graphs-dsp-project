#ifndef GRAPH_STORE
#define GRAPH_STORE

class GraphStore {
	char* storePath;
	char usedGraphId[50];

	void clear();
	void copy(const GraphStore& other);

public:
	GraphStore(const char* path);
	GraphStore(const GraphStore& other);
	GraphStore& operator=(const GraphStore& other);
	~GraphStore();

	bool isUsingGraph();
	bool graphExists(const char* graphId);
	bool nodeExists(const char* nodeId);

	bool createGraph(const char* newGraphId, bool directed);
	bool useGraph(const char* existingGraphId);
	bool deleteGraph(const char* existingGraphId);

	bool createNode(const char* newNodeId);
	bool deleteNode(const char* existingNodeId);

	bool createArc(const char* nodeId1, const char* nodeId2, int weight = 1);
	bool deleteArc(const char* nodeId1, const char* nodeId2);
};

#endif
