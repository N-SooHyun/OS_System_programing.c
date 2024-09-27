#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <direct.h>

//���Ͻý���
// �ڱ������� - �������� ���ٸ� ����
// ����-������� ����������, �˻�-���������� �˻�, ����-�����⸸ ���� �Ϻ��� ���� �����
//HDD
// HDD(��ũ) - ���� ������ ����
// ����-�����͸� ��� ������ ���� �� ��ϸ��� Ư�� �ּҸ� ����
// �˻�-�ε����� �̿��ؼ� ���� Ž�� ���� 
// ����-������ ���� ������ ��밡���� ��������� ǥ�ø� �һ� ���� ���������� ����

//�ڱ������� ���� ���� 
#define TAPE_SIZE 100		//�������� ũ��
#define MAX_FILE_SIZE 50	//������ ũ��

//�������� ����ü
typedef struct TapeFile {
	char data[MAX_FILE_SIZE];	//������ ������
}TapeFile;

TapeFile tape[TAPE_SIZE];	//�������� �迭

int fileCount = 0;		//������ ����

//������ �ڱ� �������� ����ϴ� �Լ�
void File_Tape_Write(const char* fileData) {
	if (fileCount >= TAPE_SIZE) {
		printf("�������� �� ���ֽ��ϴ�. �� �̻� ������ ����� �� �����ϴ�.\n");
		return;
	}

	//���ο� ������ �ڱ��������� ���
	strncpy_s(tape[fileCount].data, sizeof(tape[fileCount].data), fileData, MAX_FILE_SIZE);
	fileCount++;

	printf("������ ����� �Ϸ� �Ǿ����ϴ�. ������ ���� : %d\n", fileCount);
}

//������ ���������� �о�� �Լ�
void File_Tape_Read() {
	if (fileCount == 0) {
		printf("���� ������ �����ϴ�.\n");
		return;
	}
	printf("���������� ������ �о�� �� \n");
	for (int i = 0; i < fileCount; i++) {
		printf("File %d : %s\n", i, tape[i].data);
	}
}

//���������� ������ ����� ������� �����ϴ� �Լ�
void File_Tape_Delete(int index, const char* newFileData) {
	if (index < 0 || index >= fileCount) {
		printf("ã���� �ϴ� ������ �������� �ʽ��ϴ�.\n");
		return;
	}

	strncpy_s(tape[index].data, sizeof(tape[index].data), newFileData, MAX_FILE_SIZE);
	printf("���� %d��°�� ��������ϴ�.\n", index);
}

void File_Tape_main() {
	//�ڱ��������� ���� ���
	File_Tape_Write("File 1: Hello, World!");
	File_Tape_Write("File 2: Open File!");
	File_Tape_Write("File 3: C Programming!");

	//�ڱ��������� ���� ���������� �о��
	File_Tape_Read();

	//�ڱ����������� ���� ���� �� ������
	File_Tape_Delete(2, "File 2: Update");

	//�ٽ� �б�
	File_Tape_Read();
}

//HDD�� �����غ���
#define HDD_SIZE 100 //HDD�� ũ��
#define MAX_FILE_SIZE 50 //���ϴ� �ִ� ũ��

typedef struct HDDFile {
	char data[MAX_FILE_SIZE];	//������ ������
	int isDeleted;	//������ �����Ǿ����� ����
}HDDFile;

HDDFile hdd[HDD_SIZE];

//������ HDD�� ����ϴ� �Լ�
void File_HDD_Write(int index, const char* fileData) {
	if (index < 0 || index >= HDD_SIZE) {
		printf("��ȿ���� �ʴ� ��ġ �Դϴ�. ������ ����� �� �����ϴ�.\n");
		return;
	}

	strncpy_s(hdd[index].data, sizeof(hdd[index].data), fileData, MAX_FILE_SIZE);
	hdd[index].isDeleted = 1; //������ ��ȿ��
	printf("������ ���������� %d��ġ�� ����Ǿ����ϴ�.\n", index);
}

//������ �о�� �Լ�
void File_HDD_Read(int index) {
	if (index < 0 || index >= HDD_SIZE || !hdd[index].isDeleted) {
		printf("%d�� ��ġ�� ������ ���ų� �����Ǿ����ϴ�.\n", index);
		return;
	}
	printf("File %d : %s\n", index, hdd[index].data);
}

//������ �����ϴ� �Լ�
void File_HDD_Delete(int index) {
	if (index < 0 || index >= HDD_SIZE || !hdd[index].isDeleted) {
		printf("%d�� ��ġ�� ������ ���ų� �����Ǿ����ϴ�.\n", index); 
		return;
	}
	hdd[index].isDeleted = 1;
	printf("File %d�� ��ġ�� ������ ���������� �����߽��ϴ�.\n", index);
}

void File_HDD_main() {
	//HDD�� ���� ��� 
	File_HDD_Write(0, "File 1 : Hello, World!");
	File_HDD_Write(1, "File 2 : DDD");
	File_HDD_Write(2, "File 3 : ABCD File");

	//�����б�
	File_HDD_Read(2);
	File_HDD_Read(5);

	//���ϻ���
	File_HDD_Delete(1);
	File_HDD_Delete(1);

	//���� �б�
	File_HDD_Read(1);
}


//�̷������� ������ �а� ���� ������ �����ϴ�.

/*
	�׷� ������ �����ϱ�?
	File�̶� �����Ϳ� ��ɾ ��� �ִ� �߻����̰� ĸ������ ������� �����ϸ�ȴ�.
	
	1. ��������(.exe, .dll)
	������ �����ϰ��� �ϴ� ������ ���� �����̴�.(������ ���� ��ɾ� + ���࿡ ������ �Ǵ� ������)
	2. ����������(.txt, .doc, .xlsx)
	Ư�� �����͸� �����ϴ� ������ ���� �����̴�.(����� ������ + ��Ȥ ��ɾ ���� �� �ִ�. ex�׼� ��ũ��)
	3. ��ũ��Ʈ����(.py, .sh, .js, .c, .cpp)
	Ư�� ��ɾ�(��ũ��Ʈ)�� �ڵ带 ������ �����̴�.

	���ø� ���ڸ� 
	Excel.cpp -> ������ -> Excel.exe -> ���� -> Excel���μ��� �޸����� -> Excel���� �л����� ���������� ���� OS��û -> OS HDD�� Student.xlsx���� 
	-> �ŷ�ó ����.xlsx���� HDD �ҷ����� OS ��û -> OS �ŷ�ó����.xlsx���Ͽ� �����͸��� ��� ���μ��� ���� ������ ����(RAM�޸�����) -> ���� ���� ���� ��û OS �������
	�̷� �����̴�.

	�� �������� ���� �б� ���� ���� ���� ���� ���� ��û�ϴ� ���͵��� OS�̸�
	�������α׷� ������ ������ �аų� ������ ���ų� ������ �����Ҷ��� �����Ҵ� ���� �� ������ ���ؼ�
	������ �����͵��� ������ �������ش�
*/

/*
	C���� �����ϴ� stdio.h���Ͽ� �ִ� FILE ����� �ý����� OS���� ���� ��û�� �Ͽ� HDDȤ�� SSD�� ������ �ּҸ� �޾ƿͼ� ����ϴ� �����̴�.

*/
/*
//1. ��ɹ� �ޱ� vi test
//2. test��� ���� �ִ��� Ȯ�� �� ������ ���� ������ ���� ����
//3. Edit �����⿡�� ������ ���ų� ���� ��ɾ� ���� ó�� ����
//4. i��ư ���� �� �Է¸�� 
//5. esc��ư ���� �� ��ɾ���

typedef struct Copy_File_Memory {
	int size;
	int capacity;
	char* carray;
}Copy_File_Memory;

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBorders(int width, int height) {
	//��� �ϴ� ���
	for (int i = 0; i < width; i++) {
		gotoxy(i, 0);         // ��� ���
		printf("-");
		gotoxy(i, height - 1); // �ϴ� ���
		printf("-");
	}
	// ���� �� ���� ��� �׸���
	for (int i = 0; i < height; i++) {
		gotoxy(0, i);         // ���� ���
		printf("|");
		gotoxy(width - 1, i); // ���� ���
		printf("|");
	}
	gotoxy(0, 0);  // Ŀ���� ��� �������� �̵�
}

void display_FileArea(Copy_File_Memory* File_List) {
	gotoxy(2, 2);
	for (int i = 0; ; i++) {
		printf("%c", File_List->carray[i]);
		if (File_List->carray[i] == EOF)
			break;
	}	
}

void display_CommendArea() {
	gotoxy(2, 25);
	printf("\n<��ɾ� ���>\n");
	printf("1.�Է¸��, 2.����, �� �� ������  :  ");
}

void init_File_Memory_List(Copy_File_Memory* list) {
	list->size = 0;
	list->capacity = 1024; //�ʱ� �޸��Ҵ��
	list->carray = (char*)malloc(sizeof(char) * list->capacity);
}

void Add_File_Memory_List(Copy_File_Memory* list) {
	list->capacity *= 2;
	list->carray = (char*)realloc(list->carray, sizeof(char) * list->capacity);
}

int Win_Dir_Search(char *a, char *dir_list[]) {//window api�� �̿��� ���� Ž��
	WIN32_FIND_DATAW findFileData;
	HANDLE hFind = FindFirstFileA(a, &findFileData);
	int fileNum = 0;
	char* c;
	int i = 0;
	int j = 0;
	char list_name[100];
	if (hFind == INVALID_HANDLE_VALUE) {
		printf("ERROR : %lu\n", GetLastError());
		printf("No files found.\n");
	}
	else {
		do {
			if (strcmp(findFileData.cFileName, ".") != 0) {
				fileNum++;
				//printf("%d. file : ",fileNum);
				c = findFileData.cFileName;
				while (1) {
					if (c[i] <= -1)
						break;
					else if (c[i] == 0) {
						i++;
					}
					list_name[j] = c[i];
					j++;
					//printf("%c", c[i]);
					i++;
				}
				i = 0;
				j = 0;
			}
			if (list_name[0] >= -1) {
				dir_list[fileNum] = (char*)malloc(sizeof(char) * 100);
				strcpy_s(dir_list[fileNum], sizeof(char) * 100, list_name);
			}
		} while (FindNextFile(hFind, &findFileData) != 0);
		FindClose(hFind);
	}

	//printf("���� ���� : %d\n", fileNum);
	return fileNum;

}

#define FILE_NAME_LEN 50

#define ESC 27
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

void set_Cursor_Position(int x, int y) {//�Է¸�� Ŀ�� �����̱�
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void File_Sys_Input(FILE* pFile, Copy_File_Memory* File_List) {
	int keyboard;
	int cursorX = 0 , cursorY = 0;
	while (1) {
		system("cls");
		for (int i = 0; ; i++) {
			printf("%c", File_List->carray[i]);
			if (File_List->carray[i] == EOF)
				break;
		}
		printf("\n<�Է� ���>\n");
		printf("��ɾ� ���� ������ ���� �� ESC\n");
		
		while (1) {
			set_Cursor_Position(cursorX, cursorY);
			keyboard = _getch();
			switch(keyboard){
				case ESC:
					return;
				case UP_ARROW:
					if (cursorY > 0)cursorY--;
					break;
				case DOWN_ARROW:
					cursorY++;
					break;
				case LEFT_ARROW:
					if (cursorX > 0) cursorX--;
					break;
				case RIGHT_ARROW:
					cursorX++;
					break;
			}
		}
	}
}

void File_Sys_Edit(FILE* pFile, char* fileName, int keyboard, Copy_File_Memory* File_List) {
	int width = 150;
	int height = 25;
	COORD bufferSize = { width, height };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

	char NameFile[FILE_NAME_LEN];
	strcpy_s(NameFile, sizeof(char) * FILE_NAME_LEN, "FileSystem\\");
	strcat_s(NameFile, sizeof(char) * FILE_NAME_LEN, fileName);

	
	switch (keyboard) {
		case 1:	//���� ���� �о����
			printf("������ �ϴ� ���� : %s\n", fileName);
			fopen_s(&pFile, NameFile, "r");
			break;
		case 2: //���ο� ���� �����ϱ�
			break;
		default : //����
			break;
	}
	char c;
	//�޸𸮿� ���� ���� ����� ����
	for (int i = 0;; i++) {
		if (File_List->capacity <= i) {
			Add_File_Memory_List(File_List);
		}
		File_List->carray[i] = fgetc(pFile);
		if (File_List->carray[i] == EOF)
			break;
	}

	while (1) {
		system("cls");
		//�޸𸮿� ������� ���� �����
		// ��� �׸���
		drawBorders(width, height);
		// ���� ���� �� ���� ���� ���
		display_FileArea(File_List);
		display_CommendArea();
		scanf_s("%d", &keyboard);
		switch (keyboard) {
			case 1:	//���� �Է¸��
				File_Sys_Input(pFile, File_List);
				break;
			case 2: //���� ����
				break;
			default : //���Ͽ��� ������
				break;
		}
	}


	
}

void File_Sys_main() {
	Copy_File_Memory File_Memory;
	init_File_Memory_List(&File_Memory);
	char current_dir[1024];
	char* list_dir[100];
	for (int i = 0; i < 100; i++) {
		list_dir[i] = NULL;
	}
	int fileNum;
	strcpy_s(current_dir, sizeof(char) * 1024, "C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\FileSystem\\*");
	fileNum = Win_Dir_Search(current_dir, list_dir);

	
	//	for (int i = 1; i <=100; i++) {
	//		if (list_dir[i] == NULL)
	//			break;
	//		printf("%d. file : %s\n", i, list_dir[i]);
	//	}
	

	char fileName[FILE_NAME_LEN];
	char c;
	int i;
	FILE* pFile = NULL;

	int selectKeyboard = 0;

	while (1) {
		system("cls");
		printf("���� ���丮 : C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\FileSystem\n");
		printf("���丮 ���\n");
		for (int i = 1; i <= 100; i++) {
			if (list_dir[i] == NULL)
				break;
			printf("%d. file : %s\n", i, list_dir[i]);
		}
		printf("\n");
		printf("1. ���Ͽ���, 2. ���ϻ���, 3.���ϻ���, �� �� ����  :  ");
		scanf_s("%d", &selectKeyboard);

		switch (selectKeyboard) {
			case 1:
				printf("���� ���� ���� ��Ͽ��� ���� : ");
				scanf_s("%d", &selectKeyboard);
				if (selectKeyboard <= 0 || selectKeyboard > fileNum) {
					printf("��Ͽ� �������� �ʴ� �����Դϴ�.\n\n");
					break;
				}
				File_Sys_Edit(pFile, list_dir[selectKeyboard], 1, &File_Memory);
				break;
			case 2:
				printf("����� ���� ���� �Է�(������ �ִ� ���ϰ� �̸��� ��ġ�� �ȵ�) : ");
				break;
			case 3:
				printf("�����ϰ� ���� ���� ��Ͽ��� ���� : ");
				scanf_s("%d", &selectKeyboard);
				if (selectKeyboard <= 0 || selectKeyboard > fileNum) {
					printf("��Ͽ� �������� �ʴ� �����Դϴ�.\n\n");
					break;
				}
				break;
			default :
				return;
		}
	}

	
}
//�ʹ� ������� ����
*/


/*
	�׷� �� ���Ͻý����� �����ϰ���ʹ� � �����͵� ������ �������ν� ������ �����ؿԴ�.
	������ �����Ͷ� ���Ϸν� ������ �����ؿ԰� �̷��� ����� �ð��� �������� ��ȿ�����̰� �Ǿ���.
	�� ������ ������ �˾ƺ��ڴ�.

	ȸ���� ������ �����ϴ� ������ ����ٰ� ����
	1. �������� - �̸�, �������, ����ó, �ּ�, �Ի���, ���� �� �μ�
	2. �ٹ���� - ��ٽð�,��ٽð�,�ٹ��ϼ�,���� �� ��� ���, �ʰ��ٹ�
	3. �޿����� - �⺻��, ����, ���� ���� ����, �������� ����, ���ʽ� �� �μ�Ƽ��
	4. �򰡱�� - ���ֱ�, ������, ��� �ǵ��, ��ǥ�޼�����, ���� �� ���� �ʿ����
	5. �ް���û - �ް� ����, ������ �� ������, ��û��¥, ���� ����, ��밡�� �ް� �ϼ�
*/
typedef struct File_ArrayList {
	int capacity;
	char* carray;
}File_ArrayList;

void File_ArrayList_init(File_ArrayList* file_board, int keyboard) {
	switch (keyboard) {
		case 1:	//�ʱ�ȭ
			file_board->capacity = 1024;
			file_board->carray = (char*)malloc(sizeof(char) * file_board->capacity);
			break;
		case 2:	//�޸� �� �Ҵ�
			file_board->capacity *= 2;
			file_board->carray = (char*)realloc(file_board->carray, sizeof(char) * file_board->capacity);
			break;
	}
}

//���� ���� ����
FILE* File_System_Create_File(FILE** pFile, char newFile[]) {
	char FileName[100];
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, newFile);
	
	//������ ���� ���� Ȯ�� "r" �б�
	fopen_s(pFile, FileName, "r");
	
	//������ ������ ���� ��� ���� ����
	if (*pFile == NULL) {
		fopen_s(pFile, FileName, "w");
	}
	else {	//������ �����ϴ� ���
		printf("%s ������ �̹� �����մϴ�.\n", newFile); 
		return NULL;
	}

	return *pFile;
}

//���� �о����
void File_System_Read_File(FILE** pFile, char readFile[], File_ArrayList* file_board) {
	char FileName[100];
	char c;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, readFile);
	fopen_s(pFile, FileName, "r");

	if (*pFile == NULL) {
		printf("%s ������ �����ϴ�.\n",readFile);
		return;
	}
	
	//���� �޸𸮿� ����
	for (int i = 0; ; i++) {
		if (i >= file_board->capacity)
			File_ArrayList_init(file_board, 2);
		c = fgetc(*pFile);
		file_board->carray[i] = c;
		if (c == EOF)
			break;
	}

	//���� ���� ���
	printf("���� ���� %s ����\n",readFile);
	for (int i = 0; ; i++) {
		printf("%c", file_board->carray[i]);
		if (file_board->carray[i] == EOF)break;
	}
	printf("\n");

	fclose(*pFile);
}

//���� �ű��ۼ�(������ ������ ������ ��� ���� �ۼ��� ���)
void File_System_Write_File(FILE** pFile, char writeFile[], File_ArrayList* file_board) {
	char FileName[100];
	char c;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, writeFile);
	fopen_s(pFile, FileName, "w");
	//printf("%s\n", FileName);
	printf("%s ���� �ۼ�(ESC ����)\n",writeFile);
	for (int i = 0; i!=-1000; i++) {
		c = _getch();

		switch (c) {
			case 8:	//�齺���̽�
				i--;
				printf("\b \b");
				file_board->carray[i] = ' ';
				i--;
				break;
			case 13: //����
				printf("\n");
				file_board->carray[i] = '\n';
				break;
			case 32: //����
				printf(" ");
				file_board->carray[i] = '|';
				break;
			case 27: //ESC����
				file_board->carray[i] = '\0';
				i = -1001;
				break; 
			default :
				printf("%c", c);
				file_board->carray[i] = c;
				break;
		}
	}
	//���� ���Ͽ� �ű�� �۾�
	for (int i = 0; ; i++) {
		if (file_board->carray[i] == '\0') {
			fputc(file_board->carray[i], *pFile);
			break;
		}
		fputc(file_board->carray[i], *pFile);
	}
	printf("\n���� �ۼ� �Ϸ�\n");
	printf("�ۼ� �� ���� \n");
	for (int i = 0; ; i++) {
		c = file_board->carray[i];
		printf("%c", c);
		if (c == '\0')break;
	}
	printf("\n");
	fclose(*pFile);
}

//���� ���� ����
void File_System_Update_File(FILE** pFile, char updateFile[], File_ArrayList* file_board) {
	char FileName[100];
	char c;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, updateFile);
	fopen_s(pFile, FileName, "r");	//�ϴ� �о����

	for (int i = 0; ; i++) {
		c = fgetc(pFile);
		if (c == EOF) {
			file_board->carray[i] = '\0';
			break;
		}
		file_board->carray[i] = c;
	}
}

void File_System_Compony_main() {
	FILE* pFile = NULL;
	FILE* pFile_List[5];
	File_ArrayList file_board;
	File_ArrayList_init(&file_board, 1);//�ʱ�ȭ
	//ȸ�� ���� ���� ����
	pFile_List[0] = File_System_Create_File(&pFile, "Employee information");	//��������
	pFile_List[1] = File_System_Create_File(&pFile, "work record");				//�ٹ����
	pFile_List[2] = File_System_Create_File(&pFile, "salary information");		//�޿�����
	pFile_List[3] = File_System_Create_File(&pFile, "Evaluation record");		//�򰡱��
	pFile_List[4] = File_System_Create_File(&pFile, "Request for vacation");	//�ް���û
	for (int i = 0; i < 5; i++) {
		if (pFile_List[i] != NULL)
			fclose(pFile_List[i]);	//���ϻ��� ��Ʈ�� �ݾ��ֱ�
	}

	//���� ���� �б�
	File_System_Read_File(&pFile, "Employee information", &file_board);

	/*
	//���� ���� �ű� �ۼ�
	File_System_Write_File(&pFile, "Employee information", &file_board);
	File_System_Write_File(&pFile, "work record", &file_board);
	File_System_Write_File(&pFile, "salary information", &file_board);
	File_System_Write_File(&pFile, "Evaluation record", &file_board);
	File_System_Write_File(&pFile, "Request for vacation", &file_board);
	*/

	//���� ���� ����

}

//1. �ߺ��� ������
void File_System_Duplicate() {
	
}