#include <iostream>
#include "helpers/MyStrings.h"
#include "GraphStoreInputHandler.h"

int main (int argc, char *argv[]) {
	const char* pathToGraphStoreFolder = argv[1];

	GraphStoreInputHandler gsih(pathToGraphStoreFolder);
	gsih.startGettingInput();


	return 0;
}

	/*const char* str = "currently           i       gosho";
	char* word1 = new char[strlen(str, ' ') + 1];
	strcpy(word1, str, ' ');
	const char* str2 = getNextWordStart(str);
	char* word2 = new char[strlen(str2, ' ') + 1];
	strcpy(word2, str2, ' ');
	str2 = getNextWordStart(str);
	for(int i=0; i<5 && *str2 == '\0'; ++i) {
		str2 = getNextWordStart(str);
	}
	std::cout<< word1<< " "<< word2<< std::endl;*/
