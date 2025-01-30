#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

/*
	����ȭ �񵿱�ȭ �۾��� ���� ����
	����ȭ : �۾�(Task)���� ���������� ����
	�񵿱�ȭ : �۾�(Task)���� ���������� ����

	���� ��ȭ ���ؿ��� ����
	���� : ȣ���ڰ� ��ȣ������ �۾� �ϷḦ ���ŷ ���¿��� ��ٸ�
	�񵿱� : ȣ�� �� ��� ����� ��ȯ, �Ϸ� �� ��ȣ(�ݹ�/�̺�Ʈ) �߻�
*/

void Sync_process() {
	printf("���� ���μ����� Ȱ���� ����ȭ �۾�\n");

	//const char* process_1 = L"C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\x64\\Debug\\Process_Task1.exe";
	const char* process_1 = L"x64\\Debug\\Process_Task1.exe";
	const char* process_2 = L"x64\\Debug\\Process_Task2.exe";
	STARTUPINFO si1, si2;
	PROCESS_INFORMATION pi1, pi2;

	printf("1�� ���μ��� ���� \n");

	//Task1 ���μ����� ����
	ZeroMemory(&si1, sizeof(si1));
	ZeroMemory(&pi1, sizeof(pi1));
	si1.cb = sizeof(si1);

	if (!CreateProcess(
			process_1,			//������ ���α׷�
			NULL,				//����� ����(����)
			NULL,				//���μ��� ���� �Ӽ�
			NULL,				//������ ���� �Ӽ�
			FALSE,				//�θ� ���μ����� �ڵ��� �ڽ� ���μ����� ������� ����
			0,					//���� �ɼ�(�⺻��)
			NULL,				//ȯ�� ����(NULL�̸� �θ� ȯ�� ���� ���)
			NULL,				//���� ���丮 (NULL�̸� �θ� ���丮 ���)
			&si1,				//STARTUPINFO ����ü
			&pi1				//PROCESS_INFORMATION ����ü
	)) {
		printf("Task1 ���μ��� ���� ���� \n");
		return; 
	}

	//Task1�� ���������� ���
	WaitForSingleObject(pi1.hProcess, INFINITE);
	printf("1�� ���μ��� ���� \n");
	printf("\n2�� ���μ��� ���� \n");

	//Task2 ���μ��� ����
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
		printf("Task2 ���μ��� ���� ���� \n");
		return;
	}

	WaitForSingleObject(pi2.hProcess, INFINITE);
	printf("2�� ���μ��� ���� \n");

	printf("��� �۾��� �������ϴ�.\n");

	CloseHandle(pi1.hProcess);
	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hProcess);
	CloseHandle(pi2.hThread);
}

void ASync_process() {
	printf("���� ���μ����� Ȱ���� �񵿱�ȭ �۾�\n");

	//const char* process_1 = L"C:\\Users\\NSH\\Documents\\Visual_studio_pro\\OS_System_programing.c\\x64\\Debug\\Process_Task1.exe";
	const char* process_1 = L"x64\\Debug\\Process_Task1.exe";
	const char* process_2 = L"x64\\Debug\\Process_Task2.exe";
	STARTUPINFO si1, si2;
	PROCESS_INFORMATION pi1, pi2;

	printf("1�� ���μ��� ���� \n");

	//Task1 ���μ����� ����
	ZeroMemory(&si1, sizeof(si1));
	ZeroMemory(&pi1, sizeof(pi1));
	si1.cb = sizeof(si1);
	
	printf("���μ���1 ���� \n");
	if (!CreateProcess(
		process_1,			//������ ���α׷�
		NULL,				//����� ����(����)
		NULL,				//���μ��� ���� �Ӽ�
		NULL,				//������ ���� �Ӽ�
		FALSE,				//�θ� ���μ����� �ڵ��� �ڽ� ���μ����� ������� ����
		0,					//���� �ɼ�(�⺻��)
		NULL,				//ȯ�� ����(NULL�̸� �θ� ȯ�� ���� ���)
		NULL,				//���� ���丮 (NULL�̸� �θ� ���丮 ���)
		&si1,				//STARTUPINFO ����ü
		&pi1				//PROCESS_INFORMATION ����ü
	)) {
		printf("Task1 ���μ��� ���� ���� \n");
		return;
	}

	//Task2 ���μ��� ����
	ZeroMemory(&si2, sizeof(si2));
	ZeroMemory(&pi2, sizeof(pi2));
	si2.cb = sizeof(si2);

	printf("���μ���2 ����\n");
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
		printf("Task2 ���μ��� ���� ���� \n");
		return;
	}

	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);

	printf("��� �۾��� �������ϴ�.\n");

	CloseHandle(pi1.hProcess);
	CloseHandle(pi1.hThread);
	CloseHandle(pi2.hProcess);
	CloseHandle(pi2.hThread);
}


DWORD WINAPI Thread_Task1(LPVOID lpParam) {
	printf("Task1 ����\n");
	Sleep(2000); //2�� ���
	printf("Task1 ����\n"); 
	return 0;
}

DWORD WINAPI Thread_Task2(LPVOID lpParam) {
	printf("Task2 ���� \n");
	Sleep(2000); //2�� ���
	printf("Task2 ����\n");
	return 0; 
}

void Sync_thread() {
	HANDLE hThread1, hThread2;
	DWORD threadID1, threadID2;

	hThread1 = CreateThread(NULL, 0, Thread_Task1, NULL, 0, &threadID1);
	hThread2 = CreateThread(NULL, 0, Thread_Task2, NULL, 0, &threadID2);

	printf("����ȭ ó�� ����\n");

	//Task1�� ���������� ���
	WaitForSingleObject(hThread1, INFINITE);
	//Task2�� ���������� ���
	WaitForSingleObject(hThread2, INFINITE);

	printf("��� �۾��� �������ϴ�.\n");

	CloseHandle(hThread1);
	CloseHandle(hThread2);
	
}

void ASync_thread() {
	HANDLE hThread1, hThread2;
	DWORD threadID1, threadID2;

	hThread1 = CreateThread(NULL, 0, Thread_Task1, NULL, 0, &threadID1);
	hThread2 = CreateThread(NULL, 0, Thread_Task2, NULL, 0, &threadID2);

	printf("�񵿱� ó�� ����\n");

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	printf("��� �۾��� �������ϴ�.\n");

	CloseHandle(hThread1);
	CloseHandle(hThread2);

}
