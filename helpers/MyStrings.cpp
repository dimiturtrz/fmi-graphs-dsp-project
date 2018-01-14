#include "MyStrings.h"

int strlen(const char* str) {
	int i = 0;
	for(; str[i] != '\0'; ++i);
	return i;
}

void strcpy(char* destination, const char* source) {
	for(int i=0; source[i] != '\0'; i++) {
		destination[i] = source[i];
	}
	destination[strlen(source)] = '\0';
}

int strcmp(const char* str1, const char* str2) {
	if(strlen(str1) == strlen(str2)) {
		for(int i=0; str1[i] != '\0'; i++) {
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

bool isDigit(char ch) {
	return ch >= '0' && ch <= '9';
}
bool isOperator(char ch) {
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool readGenericInt(const char* str, char endSym, int& intHolder, int* lengthRead) {
	int i = 0;
	for(; str[i] == ' '; ++i);
	bool sign = true;
	if(str[i] == '-') {
		++i;
		sign = false;
	}
	int number = 0;
	for(;str[i] != endSym && str[i] != '\n' && str[i] != '\0'; i++) {
		if(isDigit(str[i])) {
			number *= 10;
			number += str[i] - '0';
		} else {
			return false;
		}
	}
	intHolder = number;
	if(lengthRead != NULL) {
		*lengthRead = i;
	}
	return true;
}
