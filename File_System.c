#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

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

/*
	�̷������� ������ �б� ���� ������ �����ϴ�.
	����ڰ� A������ ���ٰ� ������ �غ���
	HDD,SSD,������ ��� �ᱹ�� OS�� ������ �ؼ� ������ RAM�޸𸮿� �÷����ƾ��Ѵ�.
	�׷��� �� A������ HDD���� �����ϰ� �� A������ ������ RAM�޸𸮿� �÷�������
	�ΰ��� A������ ����� �Ǵ°� �׷� ����ڰ� A������ �����ϰ� ������ �ϰ� �Ǹ�
	HDD�� ��������� �����̴�.

	�׷��� OS�� ���Ͽ� ������ �� �ִ� ����� �ִٴ°� �� �� �ִµ�
	�ݴ�� �츮�� OS�� ������ �޴´ٸ� ����� ���Ͽ� ������ �������� �� �� �ִ�.

	�׷��� ������ ������� ������ �� ������?
	�츮�� ��ɾ�� �̷���� ���α׷��� �ϳ� ���� �������� .exe������ ������ٰ� ������ �غ���
	.exe������ �����ϰ� �Ǹ� OS�� RAM�޸𸮿� �����ų�ž� 
	RAM�޸𸮿� �����Ű�� RAM�޸��� ������ ������ŭ �Ҵ�޾Ƽ� CPU�� �ڿ��� ����� �� �ִ°���
	�׷��ٸ� �� .exe������ HDD�� �ִ� ������ �аų� �����Ϸ��� ��� �ؾ��ұ�?
	HDD�� �ִ� ������ RAM�޸� .exe������ �Ҵ�� ������
*/