#include<iostream>

#ifndef MY_STRINGS
#define MY_STRINGS 

//standart
int strlen(const char* str);
void strcpy(char* destination, const char* source);
int strcmp(const char* str1, const char* str2);

bool isDigit(char ch);
bool isOperator(char ch);
bool readGenericInt(const char* str, char endSym, int& intHolder, int* lengthRead);

#endif
