#include <iostream>
#include <fstream>

#include "helpers/MyStrings.h"
#include "GraphStoreInputHandler.h"

// ------------------- GRAPHSTORE METHODS --------------------------

// ------------------- GRAPH METHODS

bool GraphStoreInputHandler::createGraph(const char* arguments) {
	char* graphId = new char[strlen(arguments, ' ') + 1];
	strcpy(graphId, arguments, ' ');
	const char* remainingSubstring = getNextWordStart(arguments);

	if(graphStore.graphExists(graphId)) {
		strcpy(errorMessage, "graph with that id exists");
		return false;
	}

	if(*remainingSubstring == '\0') {
		graphStore.createGraph(graphId, false);
		return true;
	}
	if(strcmp(remainingSubstring, "directed", ' ') == 0 && *getNextWordStart(remainingSubstring) == '\0') {
		graphStore.createGraph(graphId, true);
		return true;
	}
	strcpy(errorMessage, "incorrect arguments format");
	return false;
}

bool GraphStoreInputHandler::useGraph(const char* id) {
	if(!graphStore.graphExists(id)) {
		strcpy(errorMessage, "graph with that id doesn't exist");
		return false;
	}

	graphStore.useGraph(id);
	return true;
}

bool GraphStoreInputHandler::deleteGraph(const char* id) {
	if(!graphStore.graphExists(id)) {
		strcpy(errorMessage, "graph with that id doesn't exist");
		return false;
	}

	graphStore.deleteGraph(id);
	return true;
}

// ------------------- NODE METHODS

bool GraphStoreInputHandler::createNode(const char* id) {
	if(!graphStore.isUsingGraph()) {
		strcpy(errorMessage, "no used graph");
		return false;
	}

	if(graphStore.nodeExists(id)) {
		strcpy(errorMessage, "node with that id exists");
		return false;
	}

	graphStore.createNode(id);
	return true;
}
bool GraphStoreInputHandler::deleteNode(const char* id) {
	if(!graphStore.isUsingGraph()) {
		strcpy(errorMessage, "no used graph");
		return false;
	}

	if(!graphStore.nodeExists(id)) {
		strcpy(errorMessage, "node with that id doesn't exists");
		return false;
	}

	graphStore.deleteNode(id);
	return true;
}

// ------------------- ARC METHODS

bool GraphStoreInputHandler::createArc(const char* arguments) {
	if(!graphStore.isUsingGraph()) {
		strcpy(errorMessage, "no used graph");
		return false;
	}

	const char* remainingInput = arguments;

	char* nodeId1 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(nodeId1, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	char* nodeId2 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(nodeId2, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	char* arcWeightString = new char[strlen(remainingInput, ' ') + 1];
	strcpy(arcWeightString, remainingInput, ' ');
	int arcWeight = getWeightFromWord(arcWeightString);
	remainingInput = getNextWordStart(remainingInput);

	if(*remainingInput != '\0') {
		strcpy(errorMessage, "incorrect arguments format");
		return false;
	}

	if(!graphStore.nodeExists(nodeId1) || !graphStore.nodeExists(nodeId2)) {
		strcpy(errorMessage, "one or both nodes with that id don't exist");
		return false;
	}

	graphStore.createArc(nodeId1, nodeId2, arcWeight);
	return true;
}
bool GraphStoreInputHandler::deleteArc(const char* arguments) {
	if(!graphStore.isUsingGraph()) {
		strcpy(errorMessage, "no used graph");
		return false;
	}

	const char* remainingInput = arguments;

	char* nodeId1 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(nodeId1, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	char* nodeId2 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(nodeId2, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	if(*remainingInput != '\0') {
		strcpy(errorMessage, "incorrect arguments format");
		return false;
	}

	if(!graphStore.nodeExists(nodeId1) || !graphStore.nodeExists(nodeId2)) {
		strcpy(errorMessage, "one or both nodes with that id don't exist");
		return false;
	}

	if(!graphStore.arcExists(nodeId1, nodeId2)) {
		strcpy(errorMessage, "arc don't exist");
		return false;
	}

	graphStore.deleteArc(nodeId1, nodeId2);
	return true;
}

// ---------------------------- SEARCH METHODS

bool GraphStoreInputHandler::searchPath(const char* arguments) {

	const char* remainingInput = arguments;

	char* nodeId1 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(nodeId1, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	char* nodeId2 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(nodeId2, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	char* algorithmName = new char[strlen(remainingInput, ' ') + 1];
	strcpy(algorithmName, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	if(*remainingInput != '\0') {
		strcpy(errorMessage, "incorrect arguments format");
		return false;
	}

	if(!graphStore.nodeExists(nodeId1) || !graphStore.nodeExists(nodeId2)) {
		strcpy(errorMessage, "one or both nodes with that id don't exist");
		return false;
	}

	if(strcmp(algorithmName, "bfs") == 0) {
		graphStore.bfs(nodeId1, nodeId2);
		return true;
	} else if(strcmp(algorithmName, "dfs-shortest") == 0) {
		graphStore.dfsShortest(nodeId1, nodeId2);
		return true;
	} else if(strcmp(algorithmName, "dfs-longest") == 0) {
		graphStore.dfsLongest(nodeId1, nodeId2);
		return true;
	} else if(strcmp(algorithmName, "dijkstra") == 0) {
		graphStore.dijkstra(nodeId1, nodeId2);
		return true;
	} else {
		strcpy(errorMessage, "invalid algorithm name");
		return false;
	}
}

// ------------------------------ EXIT METHOD

void GraphStoreInputHandler::exit() {
	gettingInput = false;
}

// ------------- CONSOLE INTERPRETATION METHODS --------------
bool GraphStoreInputHandler::interpretInput(const char* commandVerb, const char* commandSubject, const char* arguments) {
	if(strcmp(commandVerb, "CREATE") == 0) {
		if(strcmp(commandSubject, "GRAPH") == 0) {
			return createGraph(arguments);
		} else if(strcmp(commandSubject, "NODE") == 0) {
			return createNode(arguments);
		} else if(strcmp(commandSubject, "ARC") == 0) {
			return createArc(arguments);
		}
	} else if(strcmp(commandVerb, "DELETE") == 0) {
		if(strcmp(commandSubject, "GRAPH") == 0) {
			return deleteGraph(arguments);
		} else if(strcmp(commandSubject, "NODE") == 0) {
			return deleteNode(arguments);
		} else if(strcmp(commandSubject, "ARC") == 0) {
			return deleteArc(arguments);
		}
	} else if(strcmp(commandVerb, "USE") == 0) {
		if(strcmp(commandSubject, "GRAPH") == 0) {
			return useGraph(arguments);
		}
	} else if(strcmp(commandVerb, "SEARCH") == 0) {
		return searchPath(arguments);
	} else if(strcmp(commandVerb, "QUIT") == 0) {
		exit();
		return true;
	}
	generateStandartErrorMessage(commandVerb, commandSubject);
	return false;
}

void GraphStoreInputHandler::startGettingInput() {
	if(!(graphStore.isValid())) {
		std::cout<< "directory doesn't exist\n";
		return;
	}

	gettingInput = true;
	char commandVerb[8]; // if we get say DELETES the extra char will catch the 'S'
	char commandSubject[7];
	char arguments[512];
	int argumentOffset = 0;
	while(gettingInput) {
        std::cin.clear();
		commandSubject[0] = '\0';

		std::cin>> commandVerb;
		if(strlen(commandVerb) <= 6 && std::cin.peek() == ' ') {
			if(strcmp(commandVerb, "SEARCH") != 0) {
				std::cin>> commandSubject;
			}
		}
		std::cin.getline(arguments, 511);
		for(; arguments[argumentOffset] == ' '; ++argumentOffset);
		if(!interpretInput(commandVerb, commandSubject, arguments + argumentOffset)) {
			std::cout<< "Error: "<< errorMessage<< std::endl;
		}
	}
}

void GraphStoreInputHandler::generateStandartErrorMessage(const char* commandVerb, const char* commandSubject) {
	int i = 0;
	errorMessage[i] = '"';
	for(int l = 0; commandVerb[l] != '\0'; ++l) {
		errorMessage[++i] = commandVerb[l];
	}
	errorMessage[i] = ' ';
	for(int l = 0; commandSubject[l] != '\0'; ++l) {
		errorMessage[++i] = commandSubject[l];
	}
	strcpy(errorMessage + i, "\" is an invalid command");
}

// ------------- CONSTRUCTOR AND DESTRUCTOR -----------------
GraphStoreInputHandler::GraphStoreInputHandler(const char* pathToGraphStoreFolder): graphStore(pathToGraphStoreFolder) {}

