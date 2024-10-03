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

	//C언어에서 제공하는 stdio.h파일에 있는 FILE 입출력 시스템은 OS에게 직접 요청을 하여 HDD혹은 SSD에 파일의 주소를 받아와서 사용하는 형식이다.



/*
	그럼 이 파일시스템이 등장하고부터는 어떤 데이터든 파일의 개념으로써 관리를 진행해왔다.
	-논리적 개념 단계로써 파일을 어떻게 저장할지 생성할지-
	필드 - 한 개의 의미(ex 이름, 나이, 성별 같은 한 개의 의미를 가진 데이터를 모은것)
	레코드 - 의미들의 연관성을 가지고 묶어놓은 형태(ex 이름, 학번, 학과 라는 필드를 통해서 학생정보 라는 묶음을 만들 수 있음)
	파일 - 연관성을 가진 레코드들의 집합체 레코드가 최소 1개이상으로 나열된것(ex 학생정보 파일 이라면 학생정보레코드의 데이터들이 1개이상 나열)

	그리고 이에 따른 논리적 파일 개념뿐만 아니라 실제로 어떻게 물리적으로 저장할지에 대한것도 생각하게 되었지
	그 생각의 3가지 핵심 키워드가 존재해 저장매체, 콘텐츠, 구조로 나눌 수 있지
	-물리적 단계 3가지 키워드-
	저장매체(where) - 파일을 어디에 저장할까? HDD? SSD? CD? 테이프? 그리고 순차적 접근(HDD)으로 할까? 직접 접근(SSD)을 할까? 에 대한 고민
	콘텐츠(what) - 파일의 종류는 또 얼마나 다양해 .txt, .docs, .pdf, .c, .exe, .obj 이 처럼 데이터,실행,워크 파일 같은 여러 종류로 나뉠 수 있는 고민
	구조(How) - 그럼 이제 이 자질구래한 것들의 결정이 끝났으니 최종적으로 어떻게 저장할까? 직접접근? 순차접근? 색인순차? 링파일? 해싱?


	이런 논리적인관점과 물리적인 관점에서 파일을 쌓아 데이터를 저장하고 처리하게 되면서 발전을 해오다 결국
	이 파일 시스템이 굉장히 비효율하다는것을 깨닫는 시점이 오게 되지
	그 시점에 등장한게 데이터베이스야
	그럼 왜 파일 시스템이 비효율적이었을까?

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

//파일 이름 설정
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
	//printf("기존 파일 %s 내용\n",readFile);
	for (int i = 0; ; i++) {
		//printf("%c", file_board->carray[i]);
		if (file_board->carray[i] == EOF)break;
	}
	//printf("\n");

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

//파일 동적할당하는 인라인 함수(스택에 올라가지 않음)
inline char* file_words_add(int* maximum, char* change_file_words) {
	*maximum *= 2;
	char* new_words = (char*)realloc(change_file_words, sizeof(char) * *maximum);
	//free(change_file_words);
	if (new_words == NULL) {
		printf("메모리 할당 실패");
		exit(1);
	}
	return new_words;
}

//기존 파일 수정
void File_System_Update_File(FILE** pFile, char updateFile[], File_ArrayList* file_board) {
	//1.행열로 파싱 쪼개기 2.특정문자열수정하기 3.행열다시합치기	
	char FileName[100];
	char c;
	int selectNum;
	strcpy_s(FileName, sizeof(char) * 100, "Compony_File\\");
	strcat_s(FileName, sizeof(char) * 100, updateFile);
	fopen_s(pFile, FileName, "r");	//일단 읽어오기

	for (int i = 0; ; i++) {
		c = fgetc(*pFile);
		if (c == EOF) {
			file_board->carray[i] = '\0';
			break;
		}
		file_board->carray[i] = c;
	}
	//1
	//행의 개수 부터 파싱
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
	printf("수정 하고자 하는 행을 입력하세요 : ");
	scanf_s("%d", &selectNum);
	if (selectNum < 0 || selectNum >= row_count) {
		printf("보기에 존재하지 않는 행입니다.\n");
		return;
	}
	//선택받은 행을 기준으로 열 파싱
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
		printf("%d 번째 열의 문자열 : %s\n", i, col_line[i]);
	}

	printf("수정 하고자 하는 열을 입력하세요 : ");
	scanf_s("%d", &selectNum);
	if (selectNum < 0 || selectNum >= col_count) {
		printf("보기에 존재하지 않는 행입니다.\n");
		return;
	}
	//2
	int selectCol = selectNum;
	int max_words = 1024;
	char change_word;
	char* change_words = (char*)malloc(sizeof(char) * max_words);//수정할문자열
	printf("(%s) 수정 할 값 입력(enter:입력완료) : ", col_line[selectCol]);
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
	//3 기존 파일 수정
	//file_board->carray  <--참조   row_line  <--참조  col_line
	int max_file_words = 1024;
	char* change_file_words = (char*)malloc(sizeof(char) * max_file_words);	
	char* ptr_ch_file_words = change_file_words;
	char* ptr_carray = file_board->carray;
	int current_count = 0;

	for (int row = 0; row < row_count; row++) {//행
		if (row == selectRow) {//수정할 행일 경우
			for (int col = 0; col < col_count; col++) {//열
				if (col == selectCol) {//수정할 열일 경우
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
							//기존 carray의 위치를 옮겨줘야함
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
				else {//수정할 열이 아닌경우
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
			//열의 끝이라면
			ptr_ch_file_words[-1] = '\n';
		}
		else {	//수정할 행이 아닌경우
			for (int word_count=0; ; word_count++, current_count++) {
				if (current_count >= max_file_words)
					change_file_words = file_words_add(&max_file_words, change_file_words);
				if (ptr_carray[word_count] == '\0') {//행의 끝
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
	
	printf("파일이 성공적으로 수정이 완료 되었습니다.\n");
	printf("%s\n", change_file_words);
	
	//동적할당 해제와 더불어 파일저장
	free(file_board->carray);
	file_board->carray = change_file_words;
	free(row_line);
	free(col_line);
	free(change_words);

	//r모드로 열어놓은 pFile을 해제 이후 w모드로 다시 열어서 기존 파일내용 없애고 덮어씌우는 작업 진행
	//r : 읽기만 가능(파일없을시 에러)   w : 쓰기만가능(파일없을시 생성, 파일 있을시 내용 삭제)
	fclose(*pFile);
	fopen_s(pFile, FileName, "w");
	//마지막 문자열 '\0'까지 파일에 작성
	fputs(file_board->carray, *pFile);

	free(file_board->carray);
	fclose(*pFile);
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
	File_System_Read_File(&pFile, "Employee information2", &file_board);

	/*
	//파일 내용 신규 작성
	File_System_Write_File(&pFile, "Employee information", &file_board);
	File_System_Write_File(&pFile, "work record", &file_board);
	File_System_Write_File(&pFile, "salary information", &file_board);
	File_System_Write_File(&pFile, "Evaluation record", &file_board);
	File_System_Write_File(&pFile, "Request for vacation", &file_board);
	*/

	//파일 내용 수정
	File_System_Update_File(&pFile, "Employee information2", &file_board);
}

//해쉬테이블 생성
//key값 Name, DOB, Contact, Address, HireDate, Position, Department
//CheciIn, Checkout, Workdays, Tardiness, Absence, Overtime
//Basesalary, Allowance, Taxdeduction, Yearend, Bonus, Incentive
//Reviewcycle, Score, Feedback, Goalachieved, Trainingneeds
//Leavetype, Startdate, Enddate, Requestdate, Availableleave


// 파일 시스템의 불편한점들을 함수들로 표현해보자
//1. 중복성 문제점
void File_System_Redundancy() {
	//5개의 파일에는 5명의 이름을 토대로 정보들이 저장되어 있다. 그런데 만약 이름을 바꾸는 문제가 생긴다면?
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
	printf("수정하고자 하는 파일이 무엇인가요? \n");
	for (int i = 0; i < file_num; i++) {
		printf("%d번 : %s\n", i,File_Name[i]);
	}
	printf("선택해주세요 : ");
	scanf_s("%d", &selectNum);
	printf("수정할 파일 : %s\n", File_Name[selectNum]);
	File_System_Update_File(&pFile, File_Name[selectNum], &file_board[selectNum]);
	//파일 1에서 이름을 바꿀 시 파일 2,3,4,5에서도 동일한 이름을 변경해줘야 한다.
}


//2. 데이터 불일치
void File_System_Inconsistency() {
	//중복성이 발생해서 모두 수정해주지 않으면 발생함
	//1, 2파일이 일치하지 않는 상황이 생김
	File_System_Redundancy();

}

//3. 데이터 접근성의 제한
void File_System_Limited_Data_Access() {
	//특정 파일에 데이터를 찾으려면 파일을 순차적으로 검색하거나 특정 위치를 지정해서 접근해야하는 비효율성 발생
	//DB는 쿼리를 제공하여 검색기능으로 찾으면 쉽게 찾아짐
}

//4. 데이터 동시 접근의 어려움
void File_System_Concurrency_Issues() {
	//여러 사용자가 하나의 파일에 동시에 접근하고 수정하는것이 매우 어려움
	//또한 동시에 파일을 수정하면 손실이나 충돌이 발생할 수 있어서 한 개의 파일에 한 사람만 접근이 가능
	//DB는 트랜잭션 commit과 같은 기능들을 통해서 동시접근이 가능
}

//5. 데이터 통합의 어려움
void File_System_Data_Integration_Challenges() {
	//데이터를 여러 파일에 나눠서 저장하기에 다른 파일에서 데이터를 통합하기 어려움
	//DB 관계형 데이터 모델을 토대로 연관 관계로 효율적인 관리가 용이
}

//6. 데이터 보안의 부족
void File_System_Lack_of_Data_Security() {
	//파일 단위로 접근 권한을 부여가 가능하나 세부적인 데이터 보안기능이 부족하여 파일단위 보안 외 세밀한 관리는 어려움
	//DB 사용자별 권한제어기능으로 관리해줌
}

//7. 백업 및 복구의 어려움
void File_System_Backup_and_Recovery_Challenges() {
	//백업과 복구가 어려움 파일로 데이터가 여러개 분산되어있으면 일관성있는 백업도 손실시 복구도 복잡
	//DB 자동 백업 및 복구 기능
}