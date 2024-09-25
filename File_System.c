#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <direct.h>

//파일시스템
// 자기테이프 - 순차적인 접근만 가능
// 저장-빈공간에 순차적저장, 검색-순차적으로 검색, 삭제-덮어씌우기만 가능 완벽한 삭제 어려움
//HDD
// HDD(디스크) - 랜덤 접근이 가능
// 저장-데이터를 블록 단위로 저장 각 블록마다 특정 주소를 가짐
// 검색-인덱스를 이용해서 빠른 탐색 가능 
// 삭제-덮어씌우기 가능 삭제시 사용가능한 빈공간임을 표시만 할뿐 실제 지워지지는 않음

//자기테이프 예제 구현 
#define TAPE_SIZE 100		//테이프의 크기
#define MAX_FILE_SIZE 50	//파일의 크기

//테이프의 구조체
typedef struct TapeFile {
	char data[MAX_FILE_SIZE];	//파일의 데이터
}TapeFile;

TapeFile tape[TAPE_SIZE];	//테이프의 배열

int fileCount = 0;		//파일의 개수

//파일을 자기 테이프에 기록하는 함수
void File_Tape_Write(const char* fileData) {
	if (fileCount >= TAPE_SIZE) {
		printf("테이프가 꽉 차있습니다. 더 이상 파일을 기록할 수 없습니다.\n");
		return;
	}

	//새로운 파일을 자기테이프에 기록
	strncpy_s(tape[fileCount].data, sizeof(tape[fileCount].data), fileData, MAX_FILE_SIZE);
	fileCount++;

	printf("파일의 기록이 완료 되었습니다. 파일의 개수 : %d\n", fileCount);
}

//파일을 순차적으로 읽어내는 함수
void File_Tape_Read() {
	if (fileCount == 0) {
		printf("읽을 파일이 없습니다.\n");
		return;
	}
	printf("테이프에서 파일을 읽어내는 중 \n");
	for (int i = 0; i < fileCount; i++) {
		printf("File %d : %s\n", i, tape[i].data);
	}
}

//테이프에서 파일을 덮어쓰는 방식으로 삭제하는 함수
void File_Tape_Delete(int index, const char* newFileData) {
	if (index < 0 || index >= fileCount) {
		printf("찾고자 하는 파일이 존재하지 않습니다.\n");
		return;
	}

	strncpy_s(tape[index].data, sizeof(tape[index].data), newFileData, MAX_FILE_SIZE);
	printf("파일 %d번째에 덮어씌웠습니다.\n", index);
}

void File_Tape_main() {
	//자기테이프에 파일 기록
	File_Tape_Write("File 1: Hello, World!");
	File_Tape_Write("File 2: Open File!");
	File_Tape_Write("File 3: C Programming!");

	//자기테이프에 파일 순차적으로 읽어내기
	File_Tape_Read();

	//자기테이프에서 파일 삭제 및 덮어씌우기
	File_Tape_Delete(2, "File 2: Update");

	//다시 읽기
	File_Tape_Read();
}

//HDD를 구현해보기
#define HDD_SIZE 100 //HDD의 크기
#define MAX_FILE_SIZE 50 //파일당 최대 크기

typedef struct HDDFile {
	char data[MAX_FILE_SIZE];	//파일의 데이터
	int isDeleted;	//파일이 삭제되었는지 여부
}HDDFile;

HDDFile hdd[HDD_SIZE];

//파일을 HDD에 기록하는 함수
void File_HDD_Write(int index, const char* fileData) {
	if (index < 0 || index >= HDD_SIZE) {
		printf("유효하지 않는 위치 입니다. 파일을 기록할 수 없습니다.\n");
		return;
	}

	strncpy_s(hdd[index].data, sizeof(hdd[index].data), fileData, MAX_FILE_SIZE);
	hdd[index].isDeleted = 1; //파일이 유효함
	printf("파일이 성공적으로 %d위치에 저장되었습니다.\n", index);
}

//파일을 읽어내는 함수
void File_HDD_Read(int index) {
	if (index < 0 || index >= HDD_SIZE || !hdd[index].isDeleted) {
		printf("%d에 위치한 파일이 없거나 삭제되었습니다.\n", index);
		return;
	}
	printf("File %d : %s\n", index, hdd[index].data);
}

//파일을 삭제하는 함수
void File_HDD_Delete(int index) {
	if (index < 0 || index >= HDD_SIZE || !hdd[index].isDeleted) {
		printf("%d에 위치한 파일이 없거나 삭제되었습니다.\n", index); 
		return;
	}
	hdd[index].isDeleted = 1;
	printf("File %d에 위치한 파일을 성공적으로 삭제했습니다.\n", index);
}

void File_HDD_main() {
	//HDD에 파일 기록 
	File_HDD_Write(0, "File 1 : Hello, World!");
	File_HDD_Write(1, "File 2 : DDD");
	File_HDD_Write(2, "File 3 : ABCD File");

	//파일읽기
	File_HDD_Read(2);
	File_HDD_Read(5);

	//파일삭제
	File_HDD_Delete(1);
	File_HDD_Delete(1);

	//파일 읽기
	File_HDD_Read(1);
}


//이런식으로 파일을 읽고 쓰고 저장이 가능하다.

/*
	그럼 파일은 무엇일까?
	File이란 데이터와 명령어를 담고 있는 추상적이고 캡슐적인 문서라고 생각하면된다.
	
	1. 실행파일(.exe, .dll)
	뭔가를 실행하고자 하는 목적을 가진 파일이다.(실행을 위한 명령어 + 실행에 도움이 되는 데이터)
	2. 데이터파일(.txt, .doc, .xlsx)
	특정 데이터를 저장하는 목적을 가진 파일이다.(저장된 데이터 + 간혹 명령어가 있을 수 있다. ex액셀 메크로)
	3. 스크립트파일(.py, .sh, .js, .c, .cpp)
	특정 명령어(스크립트)나 코드를 포함한 파일이다.

	예시를 들자면 
	Excel.cpp -> 컴파일 -> Excel.exe -> 실행 -> Excel프로세스 메모리적재 -> Excel에서 학생관리 데이터파일 저장 OS요청 -> OS HDD에 Student.xlsx생성 
	-> 거래처 관리.xlsx파일 HDD 불러오기 OS 요청 -> OS 거래처관리.xlsx파일에 데이터만을 모아 프로세스 동적 영역에 복사(RAM메모리적재) -> 이후 수정 저장 요청 OS 덮어씌워줌
	이런 느낌이다.

	이 과정에서 파일 읽기 파일 쓰기 파일 삭제 등을 요청하는 모든것들은 OS이며
	응용프로그램 내에서 파일을 읽거나 파일을 쓰거나 파일을 삭제할때는 동적할당 영역 힙 영역을 통해서
	파일의 데이터들의 공간을 마련해준다
*/

/*
	C언어에서 제공하는 stdio.h파일에 있는 FILE 입출력 시스템은 OS에게 직접 요청을 하여 HDD혹은 SSD에 파일의 주소를 받아와서 사용하는 형식이다.

*/

//1. 명령문 받기 vi test
//2. test라는 파일 있는지 확인 후 없으면 생성 있으면 파일 열기
//3. Edit 편집기에서 파일을 열거나 생성 명령어 모드로 처음 진행
//4. i버튼 누를 시 입력모드 
//5. esc버튼 누를 시 명령어모드

int Win_Dir_Search(char *a, char *dir_list[]) {//window api를 이용한 파일 탐색
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

	//printf("파일 개수 : %d\n", fileNum);
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
		case 1:	//기존 파일 읽어오기
			printf("열고자 하는 파일 : %s\n", fileName);
			fopen_s(&pFile, NameFile, "r");
			break;
		case 2: //새로운 파일 생성하기
			break;
		default : //종료
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
		printf("현재 디렉토리 : C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\FileSystem\n");
		printf("디렉토리 목록\n");
		for (int i = 1; i <= 100; i++) {
			if (list_dir[i] == NULL)
				break;
			printf("%d. file : %s\n", i, list_dir[i]);
		}
		printf("\n");
		printf("1. 파일열기, 2. 파일생성, 3.파일삭제, 그 외 종료  :  ");
		scanf_s("%d", &selectKeyboard);

		switch (selectKeyboard) {
			case 1:
				printf("열고 싶은 파일 목록에서 선택 : ");
				scanf_s("%d", &selectKeyboard);
				if (selectKeyboard <= 0 || selectKeyboard > fileNum) {
					printf("목록에 존재하지 않는 파일입니다.\n\n");
					break;
				}
				File_Sys_Edit(pFile, list_dir[selectKeyboard], 1);
				break;
			case 2:
				printf("만들고 싶은 파일 입력(기존에 있는 파일과 이름이 겹치면 안됨) : ");
				break;
			case 3:
				printf("삭제하고 싶은 파일 목록에서 선택 : ");
				scanf_s("%d", &selectKeyboard);
				if (selectKeyboard <= 0 || selectKeyboard > fileNum) {
					printf("목록에 존재하지 않는 파일입니다.\n\n");
					break;
				}
				break;
			default :
				return;
		}
	}

	
}





















/*
	그럼 이 파일시스템이 등장하고부터는 어떤 데이터든 파일의 개념으로써 관리를 진행해왔다.
	간단한 데이터라도 파일로써 관리를 진행해왔고 이러한 방식은 시간이 지날수록 비효율적이게 되었다.
	이 불편한 점들을 알아보겠다.
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

//1. 중복성 문제점
void File_System_Duplicate_main() {
	//회사의 직원을 관리하는 파일을 만든다고 가정해보겠다.
	//지원정보, 근무기록, 급여정보, 평가기록, 휴가신청 총 5개의 파일을 만들어보겠다.
	//직원정보 - 이름, 생년월일, 연락처, 주소, 입사일, 직위 및 부서
	//근무기록 - 출근시간,퇴근시간,근무일수,지각 및 결근 기록, 초과근무
	//급여정보 - 기본급, 수당, 세금 공제 내역, 연말정산 정보, 보너스 및 인센티브
	//평가기록 - 평가주기, 평가점수, 상사 피드백, 목표달성여부, 교육 및 개발 필요사항
	//휴가신청 - 휴가 유형, 시작일 및 종료일, 신청날짜, 승인 상태, 사용가능 휴가 일수
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