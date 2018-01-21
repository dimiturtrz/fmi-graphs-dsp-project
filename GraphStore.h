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

	bool createGraph(const char* newGraphId, bool directed);
};

#endif
