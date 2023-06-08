#ifdef _WIN32

#include "ChessGameWindows.h"
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChessGameWindows g;
	g.setHInstance(hInstance);
    g.startLocalGame();
    return 0;
}

#else 

#include "ChessGameLinux.h"
int main() 
{
	ChessGameLinux g; 
	g.startLocalGame();
	return 0;
}

#endif



