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

//1. ��ɹ� �ޱ� vi test
//2. test��� ���� �ִ��� Ȯ�� �� ������ ���� ������ ���� ����
//3. Edit �����⿡�� ������ ���ų� ���� ��ɾ� ���� ó�� ����
//4. i��ư ���� �� �Է¸�� 
//5. esc��ư ���� �� ��ɾ���

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

void File_Sys_Input(FILE* pFile) {

}

void File_Sys_Edit(FILE* pFile, char* fileName, int keyboard) {
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
	char fileBoard[1024];
	char c;
	for (int i = 0; i < 1024; i++) {
		fileBoard[i] = fgetc(pFile);
		if (fileBoard[i] == EOF)
			break;
	}
	system("cls");
	for (int i = 0; i < 1024; i++) {
		printf("%c", fileBoard[i]);
		if (fileBoard[i] == EOF)
			break;
	}
	scanf_s("%d", &keyboard);
	
}

void File_Sys_main() {
	char current_dir[1024];
	char* list_dir[100];
	for (int i = 0; i < 100; i++) {
		list_dir[i] = NULL;
	}
	int fileNum;
	strcpy_s(current_dir, sizeof(char) * 1024, "C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\FileSystem\\*");
	fileNum = Win_Dir_Search(current_dir, list_dir);

	/*
	for (int i = 1; i <=100; i++) {
		if (list_dir[i] == NULL)
			break;
		printf("%d. file : %s\n", i, list_dir[i]);
	}
	*/

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
				File_Sys_Edit(pFile, list_dir[selectKeyboard], 1);
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





















/*
	�׷� �� ���Ͻý����� �����ϰ���ʹ� � �����͵� ������ �������ν� ������ �����ؿԴ�.
	������ �����Ͷ� ���Ϸν� ������ �����ؿ԰� �̷��� ����� �ð��� �������� ��ȿ�����̰� �Ǿ���.
	�� ������ ������ �˾ƺ��ڴ�.
*/
/*
void File_System_Staff_Information(FILE* file) {
	file = fopen("Compony_File\\Staff_Information.txt", "w");
}

void File_System_Work_Record(FILE* file) {
	file = fopen("Compony_File\\Work_Record.txt", "w");
}

void File_System_Salary_Information(FILE* file) {
	file = fopen("Compony_File\\Salary_Information.txt", "w");
}

void File_System_Evaluation_Record(FILE* file) {
	file = fopen("Compony_File\\Evaluation_Record.txt", "w");
}

void File_System_Vacation_Request(FILE* file) {
	file = fopen("Compony_File\\Vacation_Request.txt", "w");
}
*/

//1. �ߺ��� ������
void File_System_Duplicate_main() {
	//ȸ���� ������ �����ϴ� ������ ����ٰ� �����غ��ڴ�.
	//��������, �ٹ����, �޿�����, �򰡱��, �ް���û �� 5���� ������ �����ڴ�.
	//�������� - �̸�, �������, ����ó, �ּ�, �Ի���, ���� �� �μ�
	//�ٹ���� - ��ٽð�,��ٽð�,�ٹ��ϼ�,���� �� ��� ���, �ʰ��ٹ�
	//�޿����� - �⺻��, ����, ���� ���� ����, �������� ����, ���ʽ� �� �μ�Ƽ��
	//�򰡱�� - ���ֱ�, ������, ��� �ǵ��, ��ǥ�޼�����, ���� �� ���� �ʿ����
	//�ް���û - �ް� ����, ������ �� ������, ��û��¥, ���� ����, ��밡�� �ް� �ϼ�
	FILE* Staff_Information;
	FILE* Work_Record;
	FILE* Salary_Information;
	FILE* Evaluation_Record;
	FILE* Vacation_Request;

	/*Staff_Information = fopen("Compony_File\\Staff_Information.txt", "w");
	Work_Record = fopen("Compony_File\\Work_Record.txt", "w");
	Salary_Information = fopen("Compony_File\\Salary_Information.txt", "w");
	Evaluation_Record = fopen("Compony_File\\Evaluation_Record.txt", "w");
	Vacation_Request = fopen("Compony_File\\Vacation_Request.txt", "w");*/

}