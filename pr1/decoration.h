//---------------------------------------------------------------------------

#ifndef decorationH
#define decorationH
//---------------------------------------------------------------------------
#endif
#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include "Unit1.h"

class Decoration
{
	HANDLE hStopEvt;   
	HANDLE hMutex;     
	HANDLE hThread;

	DynamicArray <TShape*> lights;

	int    Mode;    

public:
	Decoration();
	~Decoration();

	int getMode();
	void setMode(int val);

	void getShapes(DynamicArray <TShape*> sh);






//	Эти методы нужно избавить от Sleep();
//	Сделать что-то типо конечных автоматов
//		То есть как в lightMode2 -> горят нечетные - первое состояние,
//									горят четные - второе состояние.

// А роль Sleep() будет выполнять:
// (140) if (WaitForSingleObject(_this->hStopEvt, 100) != WAIT_TIMEOUT) {
//                                                /\
//                                                ||
	void lightMode1();
	void lightMode2();
	void lightMode3();
	void lightModeOff();












	void start();
	void stop();

private: static DWORD WINAPI ThreadFunc(LPVOID ptr);
};

class MutexLocker
{
	HANDLE hMutex;
public:
	MutexLocker(HANDLE mutex)
		:hMutex(mutex)
	{
		WaitForSingleObject(hMutex, INFINITE);
	}
	~MutexLocker()
	{
		ReleaseMutex(hMutex);
	}
};
