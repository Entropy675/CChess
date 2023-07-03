#ifndef WINVIEW_H
#define WINVIEW_H

#include <windows.h>
#include <string>
#include "View.h"

class WinView : public View
{
public:
    WinView(Board* = nullptr, HINSTANCE = nullptr);
    ~WinView();

    void update() override;
    void toggleSize() override;
    void userInput(std::string&) override;
    void print(const std::string&) override;
    void log(const std::string&) override;

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT WindowProcInternal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	std::string* outputString;
    const wchar_t* className; // L"string"
    const wchar_t* windowName;
    HWND windowHandle; // window handle
    MSG msg = {0};

    static WinView* s_pInstance;
};

#endif
