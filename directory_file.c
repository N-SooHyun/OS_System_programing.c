#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <direct.h>
#include <stdint.h>
#include <conio.h>

void win_dir_main() {
    WIN32_FIND_DATAW findFileData;
    //HANDLE hFind = FindFirstFileA("C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\FileSystem\\*", &findFileData);
    HANDLE hFind = FindFirstFileA("C:\\*", &findFileData);
    int fileNum = 0;
    char *c;
    int i = 0;
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("ERROR : %lu\n", GetLastError());
        printf("No files found.\n");
    }
    else {
        do {
            if (strcmp(findFileData.cFileName, ".") != 0) {
                fileNum++;
                printf("found File : ");
                c = findFileData.cFileName;
                while (1) {
                    if (c[i] <= -1)
                        break;
                    else if (c[i] == 0) {
                        i++;
                    }
                    printf("%c", c[i]);
                    i++;
                }
                i = 0;
                printf("\n");
            }
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }

    printf("파일 개수 : %d\n", fileNum);
}