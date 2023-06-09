#ifdef _WIN32

#include "ChessGameWindows.h"

#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MY_ICON));
	SendMessage(GetConsoleWindow(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage(GetConsoleWindow(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

    ChessGameWindows g(nullptr, nullptr, hInstance, hIcon);
    g.runLocalGame();
    return 0;
}

#elif defined __linux__

#include "ChessGameLinux.h"
int main() 
{
	ChessGameLinux g; 
	g.runLocalGame();
	return 0;
}

#endif



