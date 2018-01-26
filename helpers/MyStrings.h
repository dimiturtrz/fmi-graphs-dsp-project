#include<iostream>

#ifndef MY_STRINGS
#define MY_STRINGS 

//standart
int strlen(const char* str, char stopSymbol = '\0');
void strcpy(char* destination, const char* source, char stopSymbol = '\0');
int strcmp(const char* str1, const char* str2, char stopSymbol = '\0');
void strcat(char* destination, const char* source);

void dynamicStrcpy(char*& destination, const char* source);
void appendComponentToPath(char*& path, const char* newComponent);
void removeLastComponentFromPath(char*& path);

const char* getNextWordStart(const char* str);
int getWeightFromWord(const char* wordStart);
int getNuberFromWord(const char* wordStart);

#endif
