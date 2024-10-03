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

	//C���� �����ϴ� stdio.h���Ͽ� �ִ� FILE ����� �ý����� OS���� ���� ��û�� �Ͽ� HDDȤ�� SSD�� ������ �ּҸ� �޾ƿͼ� ����ϴ� �����̴�.



/*
	�׷� �� ���Ͻý����� �����ϰ���ʹ� � �����͵� ������ �������ν� ������ �����ؿԴ�.
	-���� ���� �ܰ�ν� ������ ��� �������� ��������-
	�ʵ� - �� ���� �ǹ�(ex �̸�, ����, ���� ���� �� ���� �ǹ̸� ���� �����͸� ������)
	���ڵ� - �ǹ̵��� �������� ������ ������� ����(ex �̸�, �й�, �а� ��� �ʵ带 ���ؼ� �л����� ��� ������ ���� �� ����)
	���� - �������� ���� ���ڵ���� ����ü ���ڵ尡 �ּ� 1���̻����� �����Ȱ�(ex �л����� ���� �̶�� �л��������ڵ��� �����͵��� 1���̻� ����)

	�׸��� �̿� ���� ���� ���� ����Ӹ� �ƴ϶� ������ ��� ���������� ���������� ���Ѱ͵� �����ϰ� �Ǿ���
	�� ������ 3���� �ٽ� Ű���尡 ������ �����ü, ������, ������ ���� �� ����
	-������ �ܰ� 3���� Ű����-
	�����ü(where) - ������ ��� �����ұ�? HDD? SSD? CD? ������? �׸��� ������ ����(HDD)���� �ұ�? ���� ����(SSD)�� �ұ�? �� ���� ���
	������(what) - ������ ������ �� �󸶳� �پ��� .txt, .docs, .pdf, .c, .exe, .obj �� ó�� ������,����,��ũ ���� ���� ���� ������ ���� �� �ִ� ���
	����(How) - �׷� ���� �� ���������� �͵��� ������ �������� ���������� ��� �����ұ�? ��������? ��������? ���μ���? ������? �ؽ�?


	�̷� �����ΰ����� �������� �������� ������ �׾� �����͸� �����ϰ� ó���ϰ� �Ǹ鼭 ������ �ؿ��� �ᱹ
	�� ���� �ý����� ������ ��ȿ���ϴٴ°��� ���ݴ� ������ ���� ����
	�� ������ �����Ѱ� �����ͺ��̽���
	�׷� �� ���� �ý����� ��ȿ�����̾�����?

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

//���� �̸� ����
inline void File_Name_List_fun(long long* File_List_Name, int file_num) {
	for (int i = 0; i < file_num; i++) {
		switch (i) {
			case 0:
				File_List_Name[i] = "Employee information";
				break;
			case 1:
				File_List_Name[i] = "work record";
				break;
			case 2:
				File_List_Name[i] = "salary information";
				break;
			case 3:
				File_List_Name[i] = "Evaluation record";
				break;
			case 4:
				File_List_Name[i] = "Request for vacation";
				break;
			default: 
				break;
		}
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
	//printf("���� ���� %s ����\n",readFile);
	for (int i = 0; ; i++) {
		//printf("%c", file_board->carray[i]);
		if (file_board->carray[i] == EOF)break;
	}
	//printf("\n");

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

//���� �����Ҵ��ϴ� �ζ��� �Լ�(���ÿ� �ö��� ����)
inline char* file_words_add(int* maximum, char* change_file_words) {
	*maximum *= 2;
	char* new_words = (char*)realloc(change_file_words, sizeof(char) * *maximum);
	//free(change_file_words);
	if (new_words == NULL) {
		printf("�޸� �Ҵ� ����");
		exit(1);
	}
	return new_words;
}

//���� ���� ����
void File_System_Update_File(FILE** pFile, char updateFile[], File_ArrayList* file_board) {
	//1.�࿭�� �Ľ� �ɰ��� 2.Ư�����ڿ������ϱ� 3.�࿭�ٽ���ġ��	
	char FileName[100];
	char c;
	int selectNum;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, updateFile);
	fopen_s(pFile, FileName, "r");	//�ϴ� �о����

	for (int i = 0; ; i++) {
		c = fgetc(*pFile);
		if (c == EOF) {
			file_board->carray[i] = '\0';
			break;
		}
		file_board->carray[i] = c;
	}
	//1
	//���� ���� ���� �Ľ�
	int max_line_count = 1024;
	long long* row_line = (long long*)malloc(sizeof(long long) * max_line_count);
	int row_count = 1;
	row_line[row_count - 1] = file_board->carray;
	char* ckNull= NULL;
	while (1) {
		if (row_count >= max_line_count) {
			max_line_count *= 2;
			row_line = (long long*)realloc(row_line, sizeof(long long) * max_line_count);
		}
		strtok_s(row_line[row_count - 1], "\n", &row_line[row_count]);
		ckNull = row_line[row_count];
		if (*ckNull == NULL)
			break;
		row_count++;
	}
	
	for (int i = 0; i < row_count; i++) {
		printf("%d Row : %s\n", i, row_line[i]);
	}
	printf("���� �ϰ��� �ϴ� ���� �Է��ϼ��� : ");
	scanf_s("%d", &selectNum);
	if (selectNum < 0 || selectNum >= row_count) {
		printf("���⿡ �������� �ʴ� ���Դϴ�.\n");
		return;
	}
	//���ù��� ���� �������� �� �Ľ�
	int selectRow = selectNum;
	int col_count = 1;
	long long* col_line = (long long*)malloc(sizeof(long long) * max_line_count);

	col_line[col_count - 1] = row_line[selectRow];

	while (1) {
		if (col_count >= max_line_count) {
			max_line_count *= 2;
			col_line = (long long*)realloc(col_line, sizeof(long long) * max_line_count);
		}
		strtok_s(col_line[col_count - 1], "|", &col_line[col_count]);
		ckNull = col_line[col_count];
		if (*ckNull == NULL)
			break;
		col_count++;
	}

	for (int i = 0; i < col_count; i++) {
		printf("%d ��° ���� ���ڿ� : %s\n", i, col_line[i]);
	}

	printf("���� �ϰ��� �ϴ� ���� �Է��ϼ��� : ");
	scanf_s("%d", &selectNum);
	if (selectNum < 0 || selectNum >= col_count) {
		printf("���⿡ �������� �ʴ� ���Դϴ�.\n");
		return;
	}
	//2
	int selectCol = selectNum;
	int max_words = 1024;
	char change_word;
	char* change_words = (char*)malloc(sizeof(char) * max_words);//�����ҹ��ڿ�
	printf("(%s) ���� �� �� �Է�(enter:�Է¿Ϸ�) : ", col_line[selectCol]);
	while (getchar() != '\n');
	for (int i = 0; ; i++) {
		if (i >= max_words) {
			max_words *= 2;
			change_words = (char*)realloc(change_words, sizeof(char) * max_words);
		}
		change_word = getchar();
		if (change_word == '\n') {
			change_words[i] = '\0';
			break;
		}
		change_words[i] = change_word;
	}
	//3 ���� ���� ����
	//file_board->carray  <--����   row_line  <--����  col_line
	int max_file_words = 1024;
	char* change_file_words = (char*)malloc(sizeof(char) * max_file_words);	
	char* ptr_ch_file_words = change_file_words;
	char* ptr_carray = file_board->carray;
	int current_count = 0;

	for (int row = 0; row < row_count; row++) {//��
		if (row == selectRow) {//������ ���� ���
			for (int col = 0; col < col_count; col++) {//��
				if (col == selectCol) {//������ ���� ���
					for (int word_count = 0; ; word_count++, current_count++) {
						if (current_count >= max_file_words)
							change_file_words = file_words_add(&max_file_words, change_file_words);
						if (change_words[word_count] == '\0') {
							ptr_ch_file_words[word_count] = '|';
							word_count++;
							current_count++;
							if (current_count >= max_file_words)
								change_file_words = file_words_add(&max_file_words, change_file_words);
							ptr_ch_file_words = &ptr_ch_file_words[word_count];
							//���� carray�� ��ġ�� �Ű������
							for (int carray = 0; ; carray++) {
								if (ptr_carray[carray] == '\0') {
									ptr_carray = &ptr_carray[carray + 1];
									break;
								}
							}
							break;
						}
						ptr_ch_file_words[word_count] = change_words[word_count];
					}
				}
				else {//������ ���� �ƴѰ��
					for (int word_count = 0; ; word_count++, current_count++) {
						if (current_count >= max_file_words)
							change_file_words = file_words_add(&max_file_words, change_file_words);
						if (ptr_carray[word_count] == '\0') {
							ptr_ch_file_words[word_count] = '|';
							word_count++;
							current_count++;
							if (current_count >= max_file_words)
								change_file_words = file_words_add(&max_file_words, change_file_words);
							ptr_ch_file_words = &ptr_ch_file_words[word_count];
							ptr_carray = &ptr_carray[word_count];
							break;
						}
						ptr_ch_file_words[word_count] = ptr_carray[word_count];
					}
				}
			}
			//���� ���̶��
			ptr_ch_file_words[-1] = '\n';
		}
		else {	//������ ���� �ƴѰ��
			for (int word_count=0; ; word_count++, current_count++) {
				if (current_count >= max_file_words)
					change_file_words = file_words_add(&max_file_words, change_file_words);
				if (ptr_carray[word_count] == '\0') {//���� ��
					ptr_ch_file_words[word_count] = '\n';
					word_count++;
					current_count++;
					if (current_count >= max_file_words)
						change_file_words = file_words_add(&max_file_words, change_file_words);
					ptr_ch_file_words = &ptr_ch_file_words[word_count];
					ptr_carray = &ptr_carray[word_count];
					break;
				}
				ptr_ch_file_words[word_count] = ptr_carray[word_count];
			}
		}
	}
	change_file_words[current_count] = '\0';
	
	printf("������ ���������� ������ �Ϸ� �Ǿ����ϴ�.\n");
	printf("%s\n", change_file_words);
	
	//�����Ҵ� ������ ���Ҿ� ��������
	free(file_board->carray);
	file_board->carray = change_file_words;
	free(row_line);
	free(col_line);
	free(change_words);

	//r���� ������� pFile�� ���� ���� w���� �ٽ� ��� ���� ���ϳ��� ���ְ� ������ �۾� ����
	//r : �б⸸ ����(���Ͼ����� ����)   w : ���⸸����(���Ͼ����� ����, ���� ������ ���� ����)
	fclose(*pFile);
	fopen_s(pFile, FileName, "w");
	//������ ���ڿ� '\0'���� ���Ͽ� �ۼ�
	fputs(file_board->carray, *pFile);

	free(file_board->carray);
	fclose(*pFile);
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
	File_System_Read_File(&pFile, "Employee information2", &file_board);

	/*
	//���� ���� �ű� �ۼ�
	File_System_Write_File(&pFile, "Employee information", &file_board);
	File_System_Write_File(&pFile, "work record", &file_board);
	File_System_Write_File(&pFile, "salary information", &file_board);
	File_System_Write_File(&pFile, "Evaluation record", &file_board);
	File_System_Write_File(&pFile, "Request for vacation", &file_board);
	*/

	//���� ���� ����
	File_System_Update_File(&pFile, "Employee information2", &file_board);
}

//�ؽ����̺� ����
//key�� Name, DOB, Contact, Address, HireDate, Position, Department
//CheciIn, Checkout, Workdays, Tardiness, Absence, Overtime
//Basesalary, Allowance, Taxdeduction, Yearend, Bonus, Incentive
//Reviewcycle, Score, Feedback, Goalachieved, Trainingneeds
//Leavetype, Startdate, Enddate, Requestdate, Availableleave


// ���� �ý����� ������������ �Լ���� ǥ���غ���
//1. �ߺ��� ������
void File_System_Redundancy() {
	//5���� ���Ͽ��� 5���� �̸��� ���� �������� ����Ǿ� �ִ�. �׷��� ���� �̸��� �ٲٴ� ������ ����ٸ�?
	FILE* pFile = NULL;
	int file_num = 5;
	int selectNum;
	long long* File_Name = (long long)malloc(sizeof(long long) * file_num);
	File_ArrayList* file_board = (File_ArrayList*)malloc(sizeof(File_ArrayList)*file_num);
	File_Name_List_fun(File_Name, file_num);
	for (int i = 0; i < file_num; i++) {
		File_ArrayList_init(&file_board[i], 1);
		File_System_Read_File(&pFile, File_Name[i], &file_board[i]);
	}
	printf("�����ϰ��� �ϴ� ������ �����ΰ���? \n");
	for (int i = 0; i < file_num; i++) {
		printf("%d�� : %s\n", i,File_Name[i]);
	}
	printf("�������ּ��� : ");
	scanf_s("%d", &selectNum);
	printf("������ ���� : %s\n", File_Name[selectNum]);
	File_System_Update_File(&pFile, File_Name[selectNum], &file_board[selectNum]);
	//���� 1���� �̸��� �ٲ� �� ���� 2,3,4,5������ ������ �̸��� ��������� �Ѵ�.
}


//2. ������ ����ġ
void File_System_Inconsistency() {
	//�ߺ����� �߻��ؼ� ��� ���������� ������ �߻���
	//1, 2������ ��ġ���� �ʴ� ��Ȳ�� ����
	File_System_Redundancy();

}

//3. ������ ���ټ��� ����
void File_System_Limited_Data_Access() {
	//Ư�� ���Ͽ� �����͸� ã������ ������ ���������� �˻��ϰų� Ư�� ��ġ�� �����ؼ� �����ؾ��ϴ� ��ȿ���� �߻�
	//DB�� ������ �����Ͽ� �˻�������� ã���� ���� ã����
}

//4. ������ ���� ������ �����
void File_System_Concurrency_Issues() {
	//���� ����ڰ� �ϳ��� ���Ͽ� ���ÿ� �����ϰ� �����ϴ°��� �ſ� �����
	//���� ���ÿ� ������ �����ϸ� �ս��̳� �浹�� �߻��� �� �־ �� ���� ���Ͽ� �� ����� ������ ����
	//DB�� Ʈ����� commit�� ���� ��ɵ��� ���ؼ� ���������� ����
}

//5. ������ ������ �����
void File_System_Data_Integration_Challenges() {
	//�����͸� ���� ���Ͽ� ������ �����ϱ⿡ �ٸ� ���Ͽ��� �����͸� �����ϱ� �����
	//DB ������ ������ ���� ���� ���� ����� ȿ������ ������ ����
}

//6. ������ ������ ����
void File_System_Lack_of_Data_Security() {
	//���� ������ ���� ������ �ο��� �����ϳ� �������� ������ ���ȱ���� �����Ͽ� ���ϴ��� ���� �� ������ ������ �����
	//DB ����ں� �������������� ��������
}

//7. ��� �� ������ �����
void File_System_Backup_and_Recovery_Challenges() {
	//����� ������ ����� ���Ϸ� �����Ͱ� ������ �л�Ǿ������� �ϰ����ִ� ����� �սǽ� ������ ����
	//DB �ڵ� ��� �� ���� ���
}