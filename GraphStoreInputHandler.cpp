#include <iostream>
#include <fstream>

#include "helpers/MyStrings.h"
#include "GraphStoreInputHandler.h"

// ------------------- FILE METHODS --------------------------
bool GraphStoreInputHandler::open(const char* path) {
	file.open(path);
	if(file.fail()) {
		std::cout<< "opening file failed"<< std::endl;
		file.clear();
		return false;
	}
	currFilePath = new char[strlen(path)];
	strcpy(currFilePath, path);
	fileOpened = true;
	std::cout<< "file opened"<< std::endl;
	return true;
}

void GraphStoreInputHandler::close() {
	if(fileOpened) {
		file.close();
		std::cout<< "file closed successfully"<< std::endl;
	}
	fileOpened = false;
	std::cout<< "no file opened"<< std::endl;
}

void GraphStoreInputHandler::exit() {
	gettingInput = false;
}

// ------------- CONSOLE INTERPRETATION METHODS --------------
bool GraphStoreInputHandler::interpretInput(const char* command, const char* arguments) {
	if(strcmp(command, "open") == 0) {
		open(arguments + sizeof(char));
	} else if(strcmp(command, "close") == 0) {
		close();
	} else if(strcmp(command, "exit") == 0) {
		exit();
	} else if(strcmp(command, "save") == 0) {
		save();
	} else if(strcmp(command, "saveas") == 0) {
		saveas(arguments + sizeof(char));
	} else {
		return false;
	}
	return true;
}

void GraphStoreInputHandler::startGettingInput() {
	gettingInput = true;
	char command[6];
	char arguments[512];
	while(gettingInput) {
		std::cin>> command;
		std::cin.getline(arguments, 511);
		if(!interpretInput(command, arguments)) {
			std::cout<< "\""<< command<< "\" is an invalid command\n";
		}
	}
}

// ------------- CONSTRUCTOR AND DESTRUCTOR -----------------
GraphStoreInputHandler::GraphStoreInputHandler(const char* pathToGraphStoreFolder) {
	
}

