#include <iostream>
#include "helpers/MyStrings.h"
#include "GraphStoreInputHandler.h"

int main (int argc, char *argv[]) {
	const char* pathToGraphStoreFolder = argv[1];

	GraphStoreInputHandler gsih(pathToGraphStoreFolder);
	gsih.startGettingInput();

	return 0;
}
