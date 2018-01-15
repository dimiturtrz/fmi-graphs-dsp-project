#include <iostream>
#include <fstream>

#include "helpers/MyStrings.h"
#include "GraphStoreInputHandler.h"

// ------------------- GRAPHSTORE METHODS --------------------------
bool GraphStoreInputHandler::createGraph(const char* arguments) {
	// get id and directed?
	// call graph store function (new file if not existing (all graphs could be separate files))
}
bool GraphStoreInputHandler::useGraph(const char* path) {
	// graph store function - open the file of the corresponding graph (false if doesn't exist)
}
bool GraphStoreInputHandler::deleteGraph(const char* id) {
	// graph store function - delete graph with this id (false if doesn't exist)
}

bool GraphStoreInputHandler::createNode(const char* arguments) {
	// function to separate first, second id
	// graph store function - create node with first, second id and weight
	// false if no used graph
}
bool GraphStoreInputHandler::deleteNode(const char* id) {
	// gs function - delete node with id, false if no opened graph
}

bool GraphStoreInputHandler::createArc(const char* arguments) {
	// separate first, second id and weight?
	// gs function - create arc with ids, false if no opened graph
	// false if no used graph
}
bool GraphStoreInputHandler::deleteArc(const char* id) {
	// delete arc with weight
	// false if no used graph
}

void GraphStoreInputHandler::exit() {
	gettingInput = false;
}

// ------------- CONSOLE INTERPRETATION METHODS --------------
bool GraphStoreInputHandler::interpretInput(const char* commandVerb, const char* commandSubject, const char* arguments) {
	if(strcmp(commandVerb, "CREATE") == 0) {
		if(strcmp(commandSubject, "GRAPH") == 0) {
			createGraph(arguments);
		} else if(strcmp(commandSubject, "NODE") == 0) {
			createNode(arguments);
		} else if(strcmp(commandSubject, "ARC") == 0) {
			createArc(arguments);
		}
	} else if(strcmp(commandVerb, "DELETE") == 0) {
		if(strcmp(commandSubject, "GRAPH") == 0) {
			deleteGraph(arguments);
		} else if(strcmp(commandSubject, "NODE") == 0) {
			deleteNode(arguments);
		}
	} else if(strcmp(commandVerb, "USE") == 0) {
		if(strcmp(commandSubject, "GRAPH") == 0) {
			useGraph(arguments);
		}
	} else if(strcmp(commandVerb, "QUIT") == 0) {
		exit();
	} else {
		return false;
	}
	return true;
}

void GraphStoreInputHandler::startGettingInput() {
	gettingInput = true;
	char commandVerb[8]; // if we get say DELETES the extra char will catch the 'S'
	char commandSubject[7];
	char arguments[512];
	while(gettingInput) {
		std::cin>> commandVerb;
		if(strlen(commandVerb) <= 6 && std::cin.peek() == ' ') {
			std::cin>> commandSubject;
		}
		std::cin.getline(arguments, 511);
		if(!interpretInput(commandVerb, commandSubject, arguments)) {
			std::cout<< "\""<< commandVerb<< " " << commandSubject<< "\" is an invalid command\n";
		}
	}
}

// ------------- CONSTRUCTOR AND DESTRUCTOR -----------------
GraphStoreInputHandler::GraphStoreInputHandler(const char* pathToGraphStoreFolder) {
	// graph store initialization
}

