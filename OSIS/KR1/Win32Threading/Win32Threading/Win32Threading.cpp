// Win32Threading.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>


CONDITION_VARIABLE threadsSpawnedCV;
CRITICAL_SECTION   lock;
bool threadsSpawned;

DWORD WINAPI ThreadRoutine(LPVOID lpArgs)
{
	EnterCriticalSection(&lock);
	while (!threadsSpawned) {
		SleepConditionVariableCS(&threadsSpawnedCV, &lock, INFINITE);
	}
	LeaveCriticalSection(&lock);
	WakeConditionVariable(&threadsSpawnedCV);

	int threadNum;
	threadNum = *(int*)lpArgs;
	printf("Thread numbder %d is running\n", threadNum);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	threadsSpawned = false;
	int * lpArgPtr;
	const int numOfThreads = 128000;
	HANDLE handles[numOfThreads];

	InitializeConditionVariable(&threadsSpawnedCV);
	InitializeCriticalSection(&lock);


	EnterCriticalSection(&lock);
	DWORD ThreadId;
	for (i = 0; i < numOfThreads; ++i)
	{
		lpArgPtr = (int*)malloc(sizeof(int));
		*lpArgPtr = i;

		// Create threads
		handles[i] = CreateThread(NULL, 0, ThreadRoutine, lpArgPtr, 0, &ThreadId);
		if (handles[i] == NULL) {
			printf("Cannot create thread %d\n", i);
			system("PAUSE");
			LeaveCriticalSection(&lock);
			exit(-1);
		}
		else {
			printf("Thread %d is created\n", i);
		}	
	}

	LeaveCriticalSection(&lock);
	threadsSpawned = true;
	WakeConditionVariable(&threadsSpawnedCV);

	// Join threads
	for (i = 0; i < numOfThreads; ++i) {
		WaitForSingleObject(handles[i], INFINITE);
	}

	system("PAUSE");
	return 0;
}

