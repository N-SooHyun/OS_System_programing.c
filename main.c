#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <direct.h>

void main() {
	//File_Tape_main();
	//File_HDD_main();
	FILE* pFile = fopen("test.txt", "r");
	printf("%s\n", pFile);
	fclose(pFile);
	return 0;
}