#include "WinView.h"
#include <gl/GL.h>
#include <stdexcept>

WinView* WinView::s_pInstance = nullptr; // will only allow one windowproc to happen at a time

WinView::WinView(Board* g, HINSTANCE hinst) 
    : View(g), outputString(nullptr), className(L"ChessWindowClass"), windowName(L"ChessWindow"), windowHandle(nullptr)
{
    int numAttempts = 3; 

	//HICON hIcon ;

	WNDCLASSW wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hinst;
	wc.lpszClassName = className;
	wc.hCursor = NULL; // Use the default cursor
	//wc.hIcon = hIcon;
	RegisterClassW(&wc);

    for (int i = 0; i < numAttempts; ++i)
    {
        windowHandle = CreateWindowExW(
            0,                              // Optional window styles
            className,                      // Window class name
            windowName,                     // Window title
            WS_OVERLAPPEDWINDOW & ~(WS_SIZEBOX | WS_MAXIMIZEBOX),            // Window style
            CW_USEDEFAULT, CW_USEDEFAULT, 
			windowWidth, windowHeight,      // Size and position
            NULL,                           // Parent window
            NULL,                           // Menu
            hinst,                          // Instance handle
            NULL                            // Additional application data
        );
        
        if (windowHandle != NULL)
            break; 
    }
    
    if (windowHandle == NULL)
    {
		std::cout << "WinView failed to acquire window handle (tried 3 times) --- CreateWindowEx failed, low resources?" << std::endl;
        throw std::runtime_error("WinView failed to acquire window handle (tried 3 times) --- CreateWindowEx failed, low resources?");
    }
	
	HDC hdc = GetDC(windowHandle);
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);
	
	SendMessage(windowHandle, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    SendMessage(windowHandle, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
	
    // Set the window class icon
    //SetClassLongPtr(windowHandle, GCLP_HICON, (LONG_PTR)hIcon);
	
    // Store the instance pointer in the static member variable
    s_pInstance = this;
	ShowWindow(windowHandle, SW_SHOW); 
}

WinView::~WinView()
{
    UnregisterClassW(className, nullptr);

    if (windowHandle != nullptr)
    {
        DestroyWindow(windowHandle);
        windowHandle = nullptr;
    }
}

void WinView::setHIcon(HICON hi)
{
	hIcon = hi;
}

// static wrapper function for win procedure
LRESULT CALLBACK WinView::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Retrieve the WinView instance pointer
    WinView* pWinView = s_pInstance;

    if (pWinView != nullptr) // Call the non-static member function inside the WinView instance
        return pWinView->WindowProcInternal(hwnd, uMsg, wParam, lParam);

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// The non-static member function handling the window procedure internally
LRESULT WinView::WindowProcInternal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //UpdateWindow(hwnd);
	
	if(outputString == nullptr)
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		
	//std::cout << "Captured input... " << *outputString << std::endl;
    switch (uMsg)
    {
		case WM_MOUSEMOVE:
		{
			int xPos = LOWORD(lParam);
			int yPos = HIWORD(lParam);


			// Track the mouse position and update your program accordingly
			std::cout << xPos << "," << yPos << std::endl;

			return 0;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			// Perform drawing operations using OpenGL
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw your chess board and pieces using OpenGL commands

			SwapBuffers(hdc);

			EndPaint(hwnd, &ps);
			return 0;
		}
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    // Handle the default behavior
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// happens whenever a logical change in the program occurs (a move is made, board is updated, piece promoted etc)
// so anything that updates based off of those things should be redrawn here.
void WinView::update() 
{
	updateBoard();
}

void WinView::updateBoard()
{
	// redraw the board on the screen
}

void WinView::toggleSize()
{
	// this can be left empty unless a toggle is needed... (maybe it toggles resizable?)
}

void WinView::userInput(std::string& a)
{
    s_pInstance = this;
	outputString = &a; // stash for later
    if (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); // sends to window proc
    }
    else
    {
        a = "exit";
		TranslateMessage(&msg);
        DispatchMessage(&msg); 
    }
	
}

void WinView::print(const std::string&)
{
	// create a chatbox that can be printed to
}

void WinView::log(const std::string&)
{
	// allow for some sort of logging (maybe to the chatbox too?)
}
