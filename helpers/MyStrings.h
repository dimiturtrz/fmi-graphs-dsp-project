#include<iostream>

#ifndef MY_STRINGS
#define MY_STRINGS 

//standart
int strlen(const char* str, char stopSymbol = '\0');
void strcpy(char* destination, const char* source, char stopSymbol = '\0');
int strcmp(const char* str1, const char* str2, char stopSymbol = '\0');

const char* getNextWordStart(const char* str);

#endif
