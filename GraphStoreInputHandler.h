#ifndef GRAPH_STORE_INPUT_HANDLER
#define GRAPH_STORE_INPUT_HANDLER

class GraphStoreInputHandler {
private:
	static const char* graphStoreFileName = "graphStore.txt";
	std::fstream file;
	bool gettingInput;
	bool fileOpened;

	bool interpretInput(const char* command, const char* arguments);

	bool open(const char* path);
	void close();
	bool save();
	bool saveas(const char* path);
	void exit();
public:
	void startGettingInput();
	bool isValidFolder();
	GraphStoreInputHandler(const char* pathToGraphStoreFolder);
	// destructor to make sure the file is closed
	~GraphStoreInputHandler(); 
};

#endif
