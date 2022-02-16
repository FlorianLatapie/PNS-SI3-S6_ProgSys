#include <stdio.h>

_declspec(dllexport) void PrintStop(char*);

void PrintStop(char* msg) {
	printf("%s\n", msg);
	getchar(); 
}