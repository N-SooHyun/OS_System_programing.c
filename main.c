#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <direct.h>
#include <stdint.h>
#include <conio.h>


void main() {
	//File_Tape_main();
	//File_HDD_main();

	File_Sys_main();

	//win_dir_main();

	

	
	
	/*strcpy_s(fileName, sizeof(char) * FILE_NAME_LEN, "FileSystem\\");
	i = strnlen_s(fileName, FILE_NAME_LEN);

	while ((c = getchar()) != '\n') {
		if (i >= FILE_NAME_LEN) {
			printf("파일명이 너무 큽니다. (50자)");
			break;
		}
		fileName[i] = c;
		i++;
	}
	fileName[i] = '\0';

	fopen_s(&pFile, &fileName, "r");

	if (pFile == NULL)
		fopen_s(&pFile, &fileName, "w");

	printf("%p\n", pFile);
	printf("%p\n", *pFile);*/

	

}