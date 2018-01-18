#include "MyStrings.h"

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
		accum = accum*multiply + (wordStart[i++] - '0');
	}

	return accum;
}
