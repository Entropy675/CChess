#ifndef CHESSGAMEWINDOWS_H
#define CHESSGAMEWINDOWS_H

#include "ChessGame.h"
#include "Windows.h"
#include "WinView.h"

class ChessGameWindows : public ChessGame
{
	public:
	ChessGameWindows(View* = nullptr, View* = nullptr, HINSTANCE = nullptr, HICON = nullptr);
	~ChessGameWindows();
	
	
	virtual void runLocalGame() override;

	protected:
	HINSTANCE hinst;
	HICON hIcon;
};

#endif
