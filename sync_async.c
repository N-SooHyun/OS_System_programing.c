#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/*
	동기화 비동기화 작업에 대한 공부
	동기화 : 작업(Task)들을 순차적으로 실행
	비동기화 : 작업(Task)들을 독립적으로 실행

	좀더 심화 수준에서 정의
	동기 : 호출자가 피호출자의 작업 완료를 블로킹 상태에서 기다림
	비동기 : 호출 후 즉시 제어권 반환, 완료 시 신호(콜백/이벤트) 발생
*/

void Sync_process() {
	printf("다중 프로세스를 활용한 동기화 작업\n");

	//const char* process_1 = L"C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\x64\\Debug\\Process_Task1.exe";
	const char* process_1 = L"x64\\Debug\\Process_Task1.exe";
	const char* process_2 = L"x64\\Debug\\Process_Task2.exe";
	STARTUPINFO si1, si2;
	PROCESS_INFORMATION pi1, pi2;

	printf("1번 프로세스 시작 \n");

	//Task1 프로세스를 생성
	ZeroMemory(&si1, sizeof(si1));
	ZeroMemory(&pi1, sizeof(pi1));
	si1.cb = sizeof(si1);

	if (!CreateProcess(
			process_1,			//실행할 프로그램
			NULL,				//명령줄 인자(없음)
			NULL,				//프로세스 보안 속성
			NULL,				//스레드 보안 속성
			FALSE,				//부모 프로세스의 핸들을 자식 프로세스로 상속하지 않음
			0,					//생성 옵션(기본값)
			NULL,				//환경 변수(NULL이면 부모 환경 변수 사용)
			NULL,				//현재 디렉토리 (NULL이면 부모 디렉토리 사용)
			&si1,				//STARTUPINFO 구조체
			&pi1				//PROCESS_INFORMATION 구조체
	)) {
		printf("Task1 프로세스 생성 실패 \n");
		return; 
	}

	//Task1이 끝날때까지 대기
	WaitForSingleObject(pi1.hProcess, INFINITE);
	printf("1번 프로세스 종료 \n");
	printf("\n2번 프로세스 시작 \n");

	//Task2 프로세스 생성
	ZeroMemory(&si2, sizeof(si2));
	ZeroMemory(&pi2, sizeof(pi2));
	si2.cb = sizeof(si2);

	if (!CreateProcess(
		process_2,
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si2,
		&pi2
	)) {
		printf("Task2 프로세스 생성 실패 \n");
		return;
	}

	WaitForSingleObject(pi2.hProcess, INFINITE);
	printf("2번 프로세스 종료 \n");

	printf("모든 작업이 끝났습니다.\n");

	CloseHandle(pi1.hProcess);
	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hProcess);
	CloseHandle(pi2.hThread);
}

void ASync_process() {
	printf("다중 프로세스를 활용한 비동기화 작업\n");

	//const char* process_1 = L"C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\x64\\Debug\\Process_Task1.exe";
	const char* process_1 = L"x64\\Debug\\Process_Task1.exe";
	const char* process_2 = L"x64\\Debug\\Process_Task2.exe";
	STARTUPINFO si1, si2;
	PROCESS_INFORMATION pi1, pi2;

	printf("1번 프로세스 시작 \n");

	//Task1 프로세스를 생성
	ZeroMemory(&si1, sizeof(si1));
	ZeroMemory(&pi1, sizeof(pi1));
	si1.cb = sizeof(si1);
	
	printf("프로세스1 생성 \n");
	if (!CreateProcess(
		process_1,			//실행할 프로그램
		NULL,				//명령줄 인자(없음)
		NULL,				//프로세스 보안 속성
		NULL,				//스레드 보안 속성
		FALSE,				//부모 프로세스의 핸들을 자식 프로세스로 상속하지 않음
		0,					//생성 옵션(기본값)
		NULL,				//환경 변수(NULL이면 부모 환경 변수 사용)
		NULL,				//현재 디렉토리 (NULL이면 부모 디렉토리 사용)
		&si1,				//STARTUPINFO 구조체
		&pi1				//PROCESS_INFORMATION 구조체
	)) {
		printf("Task1 프로세스 생성 실패 \n");
		return;
	}

	//Task2 프로세스 생성
	ZeroMemory(&si2, sizeof(si2));
	ZeroMemory(&pi2, sizeof(pi2));
	si2.cb = sizeof(si2);

	printf("프로세스2 생성\n");
	if (!CreateProcess(
		process_2,
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si2,
		&pi2
	)) {
		printf("Task2 프로세스 생성 실패 \n");
		return;
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	printf("모든 작업이 끝났습니다.\n");

	CloseHandle(pi1.hProcess);
	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hProcess);
	CloseHandle(pi2.hThread);
}


DWORD WINAPI Thread_Task1(LPVOID lpParam) {
	printf("Task1 시작\n");
	Sleep(2000); //2초 대기
	printf("Task1 종료\n"); 
	return 0;
}

DWORD WINAPI Thread_Task2(LPVOID lpParam) {
	printf("Task2 시작 \n");
	Sleep(2000); //2초 대기
	printf("Task2 종료\n");
	return 0; 
}

void Sync_thread() {
	HANDLE hThread1, hThread2;
	DWORD threadID1, threadID2;

	hThread1 = CreateThread(NULL, 0, Thread_Task1, NULL, 0, &threadID1);
	hThread2 = CreateThread(NULL, 0, Thread_Task2, NULL, 0, &threadID2);

	printf("동기화 처리 시작\n");

	//Task1이 끝날때까지 대기
	WaitForSingleObject(hThread1, INFINITE);
	//Task2가 끝날때까지 대기
	WaitForSingleObject(hThread2, INFINITE);

	printf("모든 작업이 끝났습니다.\n");

	CloseHandle(hThread1);
	CloseHandle(hThread2);
	
}

void ASync_thread() {
	HANDLE hThread1, hThread2;
	DWORD threadID1, threadID2;

	hThread1 = CreateThread(NULL, 0, Thread_Task1, NULL, 0, &threadID1);
	hThread2 = CreateThread(NULL, 0, Thread_Task2, NULL, 0, &threadID2);

	printf("비동기 처리 시작\n");

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	printf("모든 작업이 끝났습니다.\n");

	CloseHandle(hThread1);
	CloseHandle(hThread2);

}
