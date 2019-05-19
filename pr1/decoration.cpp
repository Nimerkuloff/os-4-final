// ---------------------------------------------------------------------------

#pragma hdrstop

#include "decoration.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

Decoration::Decoration() {
	hStopEvt = CreateEvent(NULL, TRUE, TRUE, NULL);
	hMutex = CreateMutex(NULL, FALSE, NULL);
	hThread = INVALID_HANDLE_VALUE;
	Mode = 0;

}

Decoration::~Decoration() {
	stop();

	CloseHandle(hStopEvt);
	CloseHandle(hMutex);

}

void Decoration::start() {
	if (hThread != INVALID_HANDLE_VALUE)
		return; 
	ResetEvent(hStopEvt);

	hThread = CreateThread(NULL, 0, ThreadFunc, this, 0, NULL);
	

}

void Decoration::stop() {

	if (hThread == INVALID_HANDLE_VALUE)
		return;
	SetEvent(hStopEvt);

	// if (WaitForSingleObject(hThread, 5000) != WAIT_OBJECT_0) {
	// TerminateThread(hThread, 1);
	// }

	CloseHandle(hThread);
	hThread = INVALID_HANDLE_VALUE;
}

int Decoration::getMode() {
	lightModeOff(); // better transition between mods
	MutexLocker guard(hMutex);
	return Mode;
}

void Decoration::setMode(int val) {
	MutexLocker guard(hMutex);
	Mode = val;
	return;
}

void Decoration::getShapes(DynamicArray<TShape*>sh) {
	lights = sh;
}

void Decoration::lightMode1() {
	for (int i = 1; i < lights.Length; i++) {
		lights[i]->Brush->Color = clRed;
		Sleep(150);
		int j = i - 1;
		if (j >= 0 && j < 9)
			lights[i]->Brush->Color = clWhite;
	}

}

void Decoration::lightMode2() {

	lights[0]->Brush->Color = clBlue;
	lights[1]->Brush->Color = clWhite;
	lights[2]->Brush->Color = clBlue;
	lights[3]->Brush->Color = clWhite;
	lights[4]->Brush->Color = clBlue;
	lights[5]->Brush->Color = clWhite;
	lights[6]->Brush->Color = clBlue;
	lights[7]->Brush->Color = clWhite;
	lights[8]->Brush->Color = clBlue;
	lights[9]->Brush->Color = clWhite;

	Sleep(200);

	lights[0]->Brush->Color = clWhite;
	lights[1]->Brush->Color = clBlue;
	lights[2]->Brush->Color = clWhite;
	lights[3]->Brush->Color = clBlue;
	lights[4]->Brush->Color = clWhite;
	lights[5]->Brush->Color = clBlue;
	lights[6]->Brush->Color = clWhite;
	lights[7]->Brush->Color = clBlue;
	lights[8]->Brush->Color = clWhite;
	lights[9]->Brush->Color = clBlue;
	Sleep(200);

}

void Decoration::lightMode3() {
	for (int i = -1; i < lights.Length; i++) {
		if (i + 1 >= 0 && i + 1 < 10)
			lights[i + 1]->Brush->Color = clRed;
		if (i + 2 >= 0 && i + 2 < 10)
			lights[i + 2]->Brush->Color = clGreen;
		if (i + 3 >= 0 && i + 3 < 10)
			lights[i + 3]->Brush->Color = clBlue;
		Sleep(200);
		if (i + 1 >= 0 && i + 1 < 10)
			lights[i + 1]->Brush->Color = clWhite;
	}

}

void Decoration::lightModeOff() {
	for (int i = 0; i < lights.Length; i++) {
		lights[i]->Brush->Color = clWhite;
	}
}

DWORD WINAPI Decoration::ThreadFunc(LPVOID ptr) {
	Decoration* _this = (Decoration*)ptr;
	if (!_this)
		return 1;

	for (; ;) {
		if (WaitForSingleObject(_this->hStopEvt, 100) != WAIT_TIMEOUT) {
			_this->lightModeOff();
			break;
		}
		switch (_this->getMode()) {
		case 1:
			_this->lightMode1();
			break;
		case 2:
			_this->lightMode2();
			break;
		case 3:
			_this->lightMode3();
			break;
		default:
			_this->lightModeOff();
			break;
		}

	}

	return 0;
}
