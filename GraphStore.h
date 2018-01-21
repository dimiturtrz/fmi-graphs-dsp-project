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
	bool arcExists(const char* nodeId1, const char* nodeId2);

	void createGraph(const char* newGraphId, bool directed);
	void useGraph(const char* existingGraphId);
	void deleteGraph(const char* existingGraphId);

	void createNode(const char* newNodeId);
	void deleteNode(const char* existingNodeId);

	void createArc(const char* nodeId1, const char* nodeId2, int weight = 1);
	void deleteArc(const char* nodeId1, const char* nodeId2);

	void bfs(const char* nodeId1, const char* nodeId2);
	void dfsShortest(const char* nodeId1, const char* nodeId2);
	void dfsLongest(const char* nodeId1, const char* nodeId2);
	void dijkstra(const char* nodeId1, const char* nodeId2);
};

#endif
