#include "MyStrings.h"

// ------------------------------- STANDART -------------------------------
int strlen(const char* str, char stopSymbol) {
	int i = 0;
	for(; str[i] != stopSymbol && str[i] != '\0'; ++i);
	return i;
}

void strcpy(char* destination, const char* source, char stopSymbol) {
	int i = 0;
	for(; source[i] != stopSymbol && source[i] != '\0'; ++i) {
		destination[i] = source[i];
	}
	destination[i] = '\0';
}

int strcmp(const char* str1, const char* str2, char stopSymbol) {
	if(strlen(str1) == strlen(str2)) {
		for(int i=0; str1[i] != stopSymbol && str1[i] != '\0'; i++) {
			if(str1[i] == str2[i]) {
				continue;
			} else {
				return (str1[i] > str2[i]) ? 1 : -1;
			}
		}
		return 0;
	}
	return (strlen(str1) > strlen(str2)) ? 1 : -1;
}

void strcat(char* destination, const char* source) {
	int destLen = strlen(destination);
	int destIter = destLen;
	for(; source[destIter - destLen] != '\0'; ++destIter) {
		destination[destIter] = source[destIter - destLen];
	}
	destination[destIter] = '\0';
}

// ------------------------------- GRAPH -------------------------------

const char* getNextWordStart(const char* str) {
	int offset = 0;
	while(str[offset] != '\0' && str[offset++] != ' ');
	while(str[offset++] != '\0' && str[offset] == ' ');
	return str + offset - 1;
}

int getWeightFromWord(const char* wordStart) {
	int i = 0;
	if(wordStart[i++] != '[') {
		return 1;
	}

	int accum = 0;
	for(int multiply = 10; wordStart[i] != ']' && wordStart[i] != '\0'; ++i) {
		accum = accum*multiply + (wordStart[i] - '0');
	}

	return accum;
}

// ------------------------------- DYNAMIC -------------------------------

void dynamicStrcpy(char*& destination, const char* source) {
	if (source == NULL) {
		return;
	}

	delete [] destination;
	destination = new char[strlen(source) + 1];
	strcpy(destination, source);
}

void appendComponentToPath(char*& path, const char* newComponent) {
	int len = strlen(path) + strlen(newComponent) + 2;
	char* newPath = new char[len];

	strcpy(newPath, path);
	strcat(newPath, "/");
	strcat(newPath, newComponent);

	delete [] path;
	path = newPath;
}

void removeLastComponentFromPath(char*& path) {
	int len = strlen(path);
	for(; path[len] != '/' && len > 0; --len);
	path[len] = '\0';
}
