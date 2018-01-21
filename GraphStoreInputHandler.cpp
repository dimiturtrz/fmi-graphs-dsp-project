#include <iostream>
#include <fstream>

#include "helpers/MyStrings.h"
#include "GraphStoreInputHandler.h"

// ------------------- GRAPHSTORE METHODS --------------------------
bool GraphStoreInputHandler::createGraph(const char* arguments) {
	char* graphId = new char[strlen(arguments, ' ') + 1];
	strcpy(graphId, arguments, ' ');
	const char* remainingSubstring = getNextWordStart(arguments);
	if(*remainingSubstring == '\0') {
		if(graphStore.createGraph(graphId, false)) {
			return true;
		} else {
			strcpy(errorMessage, "graph with that id exists");
			return false;
		}
	}
	if(strcmp(remainingSubstring, "directed", ' ') == 0 && getNextWordStart(remainingSubstring) == '\0') {
		if(graphStore.createGraph(graphId, true)) {
			return true;
		} else {
			strcpy(errorMessage, "graph with that id exists");
			return false;
		}
	}
	strcpy(errorMessage, "incorrect arguments format");
	return false;
}
bool GraphStoreInputHandler::useGraph(const char* id) {
	if(graphStore.useGraph(id)) {
		return true;
	} else {
		strcpy(errorMessage, "graph with that id doesn't exist");
		return false;
	}
}
bool GraphStoreInputHandler::deleteGraph(const char* id) {
	if(graphStore.deleteGraph(id)) {
		return true;
	} else {
		strcpy(errorMessage, "graph with that id doesn't exist");
		return false;
	}
}

bool GraphStoreInputHandler::createNode(const char* arguments) {
	// false if no used graph
	// graph store function - create node with id, false if exists
}
bool GraphStoreInputHandler::deleteNode(const char* id) {
	// gs function - delete node with id, false if no opened graph
}

bool GraphStoreInputHandler::createArc(const char* arguments) {
	// false if no used graph
	// separate first, second id and weight?
	const char* remainingInput = arguments;

	char* graphId1 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(graphId1, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	char* graphId2 = new char[strlen(remainingInput, ' ') + 1];
	strcpy(graphId2, remainingInput, ' ');
	remainingInput = getNextWordStart(remainingInput);

	char* arcWeightString = new char[strlen(remainingInput, ' ') + 1];
	strcpy(arcWeightString, remainingInput, ' ');
	int arcWeight = getWeightFromWord(arcWeightString);
	remainingInput = getNextWordStart(remainingInput);

	if(*remainingInput != '\0') {
		strcpy(errorMessage, "incorrect arguments format");
		return false;
	}
	std::cout<< "creating arc between nodes "<< graphId1<< " and "<< graphId2<< " and with weight "<< arcWeight<< std::endl;
	// gs function - create arc with id
}
bool GraphStoreInputHandler::deleteArc(const char* id) {
	// false if no used graph
	// delete arc with id
}

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
		}
	} else if(strcmp(commandVerb, "USE") == 0) {
		if(strcmp(commandSubject, "GRAPH") == 0) {
			return useGraph(arguments);
		}
	} else if(strcmp(commandVerb, "QUIT") == 0) {
		exit();
		return true;
	}
	generateStandartErrorMessage(commandVerb, commandSubject);
	return false;
}

void GraphStoreInputHandler::startGettingInput() {
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
			std::cin>> commandSubject;
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

