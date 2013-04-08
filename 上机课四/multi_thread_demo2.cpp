// multi_thread_demo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "windows.h"
#include "iostream"


using namespace std;

//�̺߳�����FuncOne
//���ܣ�ÿ�����һ����Hello��
DWORD WINAPI FuncOne(LPVOID param)
{
	while(true)
	{
		cout << "hello" << endl;
		Sleep(1000);
	}
	
	return 1;
}

//�̺߳�����FuncTwo
//���ܣ�ÿ�����һ����world��
DWORD WINAPI FuncTwo(LPVOID param)
{
	while(true)
	{
		cout << "world" << endl;
		Sleep(1000);
	}
	
	return 1;
}

int main(int argc, char* argv[])
{
	DWORD lpThread1, lpThread2;
	HANDLE hThread1;
	HANDLE hThread2;

	int iCmd = 0;

	hThread1 = CreateThread( NULL, 0, FuncOne, NULL, CREATE_SUSPENDED, &lpThread1);
	hThread2 = CreateThread( NULL, 0, FuncTwo, NULL, CREATE_SUSPENDED, &lpThread2);

	cout << "Threads created" << endl;


	while(true)
	{
		cin >> iCmd;

		if( 1 == iCmd )
		{
			cout << "resume threads" << endl;

			ResumeThread( hThread1);
			ResumeThread( hThread2);
		}
		else if( 2 == iCmd)
		{
			cout << "threads suspended" << endl;

			SuspendThread( hThread1);
			SuspendThread( hThread2);
		}
		else if( 0 == iCmd)
		{
			cout << "threads terminated" << endl;

			TerminateThread( hThread1,1);
			TerminateThread( hThread2,1);

			break;
		}
	}
	return 0;
}

