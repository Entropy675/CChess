#include "WinView.h"
#include <stdexcept>

WinView* WinView::s_pInstance = nullptr; // will only allow one windowproc to happen at a time

WinView::WinView(Board* g, HINSTANCE hinst) 
    : View(g), outputString(nullptr), className(L"ChessWindowClass"), windowName(L"ChessWindow"), windowHandle(nullptr)
{
    int numAttempts = 3; 

	std::cout << "We made it this far..." << std::endl;

    for (int i = 0; i < numAttempts; ++i)
    {
        WNDCLASSW wc = {0};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hinst;
        wc.lpszClassName = className;
        RegisterClassW(&wc);

        windowHandle = CreateWindowExW(
            0,                              // Optional window styles
            className,                      // Window class name
            windowName,                     // Window title
            WS_OVERLAPPEDWINDOW,            // Window style
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, // Size and position
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
        throw std::runtime_error("WinView failed to acquire window handle (tried 3 times) --- CreateWindowEx failed, low resources?");
    }

	std::cout << "We made it this far.2.." << std::endl;
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
	if(outputString == nullptr)
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
		
	std::cout << "Captured input... " << *outputString << std::endl;
    switch (uMsg)
    {
		case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Perform drawing operations using the HDC (device context)

            RECT rect = { 50, 50, 200, 200 };
            HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); // Red brush
            FillRect(hdc, &rect, brush);

            // Clean up
            DeleteObject(brush);
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

void WinView::update()
{
	// update the board on the screen based on the Board*
}

void WinView::toggleSize()
{
	// this can be left empty unless a toggle is needed...
}

void WinView::userInput(std::string& a)
{
    s_pInstance = this;
	outputString = &a;
    if (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); // sends to window proc
    }
    else
    {
        a = "exit";
    }
	
}

void WinView::print(const std::string&)
{
	// create a chatbox that can be printed to
}

void WinView::log(const std::string&)
{
	// allow for some sort of logging
}
