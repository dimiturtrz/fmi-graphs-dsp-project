#ifndef GRAPH_STORE_INPUT_HANDLER
#define GRAPH_STORE_INPUT_HANDLER

class GraphStoreInputHandler {
private:
	bool gettingInput;

	bool interpretInput(const char* commandVerb, const char* commandSubject, const char* arguments);

	bool createGraph(const char* arguments);
	bool useGraph(const char* path);
	bool deleteGraph(const char* id);

	bool createNode(const char* arguments);
	bool deleteNode(const char* id);

	bool createArc(const char* arguments);
	bool deleteArc(const char* id);

	void exit();
public:
	void startGettingInput();
	bool isValidFolder();
	GraphStoreInputHandler(const char* pathToGraphStoreFolder);
};

#endif
