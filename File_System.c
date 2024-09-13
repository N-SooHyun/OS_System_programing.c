#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>

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

/*
	이런식으로 파일을 읽기 쓰기 삭제가 가능하다.
	사용자가 A파일을 연다고 가정을 해보자
	HDD,SSD,테이프 모두 결국엔 OS가 접근을 해서 파일을 RAM메모리에 올려놓아야한다.
	그러면 이 A파일은 HDD에도 존재하고 이 A파일을 복사해 RAM메모리에 올려놓으니
	두개의 A파일이 생기게 되는것 그럼 사용자가 A파일을 수정하고 저장을 하게 되면
	HDD에 덮어씌워지는 개념이다.

	그러면 OS는 파일에 접근할 수 있는 방법이 있다는걸 알 수 있는데
	반대로 우리도 OS의 도움을 받는다면 충분히 파일에 접근이 가능함을 알 수 있다.

	그러면 파일을 어떤식으로 접근할 수 있을까?
	우리가 명령어로 이루어진 프로그램을 하나 만들어서 컴파일해 .exe파일을 만들었다고 가정을 해보자
	.exe파일을 실행하게 되면 OS는 RAM메모리에 적재시킬거야 
	RAM메모리에 적재시키면 RAM메모리의 정해진 공간만큼 할당받아서 CPU의 자원을 사용할 수 있는거지
	그렇다면 이 .exe파일이 HDD에 있는 파일을 읽거나 저장하려면 어떻게 해야할까?
	HDD의 있는 파일을 RAM메모리 .exe파일이 할당된 공간에
*/