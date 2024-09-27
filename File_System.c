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
/*
//1. 명령문 받기 vi test
//2. test라는 파일 있는지 확인 후 없으면 생성 있으면 파일 열기
//3. Edit 편집기에서 파일을 열거나 생성 명령어 모드로 처음 진행
//4. i버튼 누를 시 입력모드 
//5. esc버튼 누를 시 명령어모드

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
	//상단 하단 경계
	for (int i = 0; i < width; i++) {
		gotoxy(i, 0);         // 상단 경계
		printf("-");
		gotoxy(i, height - 1); // 하단 경계
		printf("-");
	}
	// 좌측 및 우측 경계 그리기
	for (int i = 0; i < height; i++) {
		gotoxy(0, i);         // 좌측 경계
		printf("|");
		gotoxy(width - 1, i); // 우측 경계
		printf("|");
	}
	gotoxy(0, 0);  // 커서를 상단 좌측으로 이동
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
	printf("\n<명령어 모드>\n");
	printf("1.입력모드, 2.저장, 그 외 나가기  :  ");
}

void init_File_Memory_List(Copy_File_Memory* list) {
	list->size = 0;
	list->capacity = 1024; //초기 메모리할당양
	list->carray = (char*)malloc(sizeof(char) * list->capacity);
}

void Add_File_Memory_List(Copy_File_Memory* list) {
	list->capacity *= 2;
	list->carray = (char*)realloc(list->carray, sizeof(char) * list->capacity);
}

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

#define ESC 27
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77

void set_Cursor_Position(int x, int y) {//입력모드 커서 움직이기
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
		printf("\n<입력 모드>\n");
		printf("명령어 모드로 나갈길 원할 시 ESC\n");
		
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
		case 1:	//기존 파일 읽어오기
			printf("열고자 하는 파일 : %s\n", fileName);
			fopen_s(&pFile, NameFile, "r");
			break;
		case 2: //새로운 파일 생성하기
			break;
		default : //종료
			break;
	}
	char c;
	//메모리에 파일 덮어 씌우는 과정
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
		//메모리에 덮어씌워진 파일 출력함
		// 경계 그리기
		drawBorders(width, height);
		// 파일 영역 및 상태 영역 출력
		display_FileArea(File_List);
		display_CommendArea();
		scanf_s("%d", &keyboard);
		switch (keyboard) {
			case 1:	//파일 입력모드
				File_Sys_Input(pFile, File_List);
				break;
			case 2: //파일 저장
				break;
			default : //파일에서 나가기
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
				File_Sys_Edit(pFile, list_dir[selectKeyboard], 1, &File_Memory);
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
//너무 어려워서 포기
*/


/*
	그럼 이 파일시스템이 등장하고부터는 어떤 데이터든 파일의 개념으로써 관리를 진행해왔다.
	간단한 데이터라도 파일로써 관리를 진행해왔고 이러한 방식은 시간이 지날수록 비효율적이게 되었다.
	이 불편한 점들을 알아보겠다.

	회사의 직원을 관리하는 파일을 만든다고 가정
	1. 직원정보 - 이름, 생년월일, 연락처, 주소, 입사일, 직위 및 부서
	2. 근무기록 - 출근시간,퇴근시간,근무일수,지각 및 결근 기록, 초과근무
	3. 급여정보 - 기본급, 수당, 세금 공제 내역, 연말정산 정보, 보너스 및 인센티브
	4. 평가기록 - 평가주기, 평가점수, 상사 피드백, 목표달성여부, 교육 및 개발 필요사항
	5. 휴가신청 - 휴가 유형, 시작일 및 종료일, 신청날짜, 승인 상태, 사용가능 휴가 일수
*/
typedef struct File_ArrayList {
	int capacity;
	char* carray;
}File_ArrayList;

void File_ArrayList_init(File_ArrayList* file_board, int keyboard) {
	switch (keyboard) {
		case 1:	//초기화
			file_board->capacity = 1024;
			file_board->carray = (char*)malloc(sizeof(char) * file_board->capacity);
			break;
		case 2:	//메모리 더 할당
			file_board->capacity *= 2;
			file_board->carray = (char*)realloc(file_board->carray, sizeof(char) * file_board->capacity);
			break;
	}
}

//파일 새로 생성
FILE* File_System_Create_File(FILE** pFile, char newFile[]) {
	char FileName[100];
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, newFile);
	
	//파일의 존재 여부 확인 "r" 읽기
	fopen_s(pFile, FileName, "r");
	
	//파일이 완전히 없는 경우 새로 생성
	if (*pFile == NULL) {
		fopen_s(pFile, FileName, "w");
	}
	else {	//파일이 존재하는 경우
		printf("%s 파일이 이미 존재합니다.\n", newFile); 
		return NULL;
	}

	return *pFile;
}

//파일 읽어오기
void File_System_Read_File(FILE** pFile, char readFile[], File_ArrayList* file_board) {
	char FileName[100];
	char c;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, readFile);
	fopen_s(pFile, FileName, "r");

	if (*pFile == NULL) {
		printf("%s 파일이 없습니다.\n",readFile);
		return;
	}
	
	//파일 메모리에 복사
	for (int i = 0; ; i++) {
		if (i >= file_board->capacity)
			File_ArrayList_init(file_board, 2);
		c = fgetc(*pFile);
		file_board->carray[i] = c;
		if (c == EOF)
			break;
	}

	//기존 파일 출력
	printf("기존 파일 %s 내용\n",readFile);
	for (int i = 0; ; i++) {
		printf("%c", file_board->carray[i]);
		if (file_board->carray[i] == EOF)break;
	}
	printf("\n");

	fclose(*pFile);
}

//파일 신규작성(파일은 있으나 내용이 없어서 새로 작성할 경우)
void File_System_Write_File(FILE** pFile, char writeFile[], File_ArrayList* file_board) {
	char FileName[100];
	char c;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, writeFile);
	fopen_s(pFile, FileName, "w");
	//printf("%s\n", FileName);
	printf("%s 파일 작성(ESC 종료)\n",writeFile);
	for (int i = 0; i!=-1000; i++) {
		c = _getch();

		switch (c) {
			case 8:	//백스페이스
				i--;
				printf("\b \b");
				file_board->carray[i] = ' ';
				i--;
				break;
			case 13: //엔터
				printf("\n");
				file_board->carray[i] = '\n';
				break;
			case 32: //공백
				printf(" ");
				file_board->carray[i] = '|';
				break;
			case 27: //ESC종료
				file_board->carray[i] = '\0';
				i = -1001;
				break; 
			default :
				printf("%c", c);
				file_board->carray[i] = c;
				break;
		}
	}
	//실제 파일에 옮기는 작업
	for (int i = 0; ; i++) {
		if (file_board->carray[i] == '\0') {
			fputc(file_board->carray[i], *pFile);
			break;
		}
		fputc(file_board->carray[i], *pFile);
	}
	printf("\n파일 작성 완료\n");
	printf("작성 된 파일 \n");
	for (int i = 0; ; i++) {
		c = file_board->carray[i];
		printf("%c", c);
		if (c == '\0')break;
	}
	printf("\n");
	fclose(*pFile);
}

//기존 파일 수정
void File_System_Update_File(FILE** pFile, char updateFile[], File_ArrayList* file_board) {
	char FileName[100];
	char c;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, updateFile);
	fopen_s(pFile, FileName, "r");	//일단 읽어오기

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
	File_ArrayList_init(&file_board, 1);//초기화
	//회사 관리 파일 생성
	pFile_List[0] = File_System_Create_File(&pFile, "Employee information");	//직원정보
	pFile_List[1] = File_System_Create_File(&pFile, "work record");				//근무기록
	pFile_List[2] = File_System_Create_File(&pFile, "salary information");		//급여정보
	pFile_List[3] = File_System_Create_File(&pFile, "Evaluation record");		//평가기록
	pFile_List[4] = File_System_Create_File(&pFile, "Request for vacation");	//휴가신청
	for (int i = 0; i < 5; i++) {
		if (pFile_List[i] != NULL)
			fclose(pFile_List[i]);	//파일생성 스트림 닫아주기
	}

	//기존 파일 읽기
	File_System_Read_File(&pFile, "Employee information", &file_board);

	/*
	//파일 내용 신규 작성
	File_System_Write_File(&pFile, "Employee information", &file_board);
	File_System_Write_File(&pFile, "work record", &file_board);
	File_System_Write_File(&pFile, "salary information", &file_board);
	File_System_Write_File(&pFile, "Evaluation record", &file_board);
	File_System_Write_File(&pFile, "Request for vacation", &file_board);
	*/

	//파일 내용 수정

}

//1. 중복성 문제점
void File_System_Duplicate() {
	
}