#include"Calc.h"

extern HINSTANCE g_hInstance;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	g_hInstance = hInstance;
	//Ö÷´°¿Ú
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN_CALC), nullptr, CalcProc);
	return 0;
}  