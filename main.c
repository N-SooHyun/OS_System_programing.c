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
	//win_dir_main();

	//File_System_Compony_main();

	char c[] = "John Smith|Vacation|2024-07-01|2024-07-10|2024-06-20|Approved|12\nEmily Johnson | Sick Leave | 2024 - 08 - 05 | 2024 - 08 - 06 | 2024 - 08 - 01 | Approved | 10\nJohn Smith|Vacation|2024-07-01|2024-07-10|2024-06-20|Approved|12";
	char* line=NULL;
	strtok_s(c, "\n", &line);
	printf("%p\n", c);
	printf("%p\n", line);
	printf("%s\n", line);
	

}