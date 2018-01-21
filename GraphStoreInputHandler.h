#include "GraphStore.h"

#ifndef GRAPH_STORE_INPUT_HANDLER
#define GRAPH_STORE_INPUT_HANDLER

class GraphStoreInputHandler {
private:
	GraphStore graphStore;
	bool gettingInput;
	char errorMessage[1024];

	bool interpretInput(const char* commandVerb, const char* commandSubject, const char* arguments);

	void generateStandartErrorMessage(const char* commandVerb, const char* commandSubject);

	bool createGraph(const char* arguments);
	bool useGraph(const char* id);
	bool deleteGraph(const char* id);

	bool createNode(const char* id);
	bool deleteNode(const char* id);

	bool createArc(const char* arguments);
	bool deleteArc(const char* arguments);

	bool searchPath(const char* arguments);

	void exit();
public:
	void startGettingInput();
	bool isValidFolder();
	GraphStoreInputHandler(const char* pathToGraphStoreFolder);
};

#endif
