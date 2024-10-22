#ifndef CHESSGAMEWINDOWS_H
#define CHESSGAMEWINDOWS_H

#include "ChessGame.h"

#include <string>
#include <cstring>
#include <regex>
#include <iostream>
#include <vector>

#include "Board.h"
#include "View.h"
#include "Log.h"
#include "Windows.h"
#include "WinView.h"

class ChessGameWindows : public ChessGame
{
	public:
	ChessGameWindows(View* = nullptr, View* = nullptr);
	~ChessGameWindows();
	
	void setHInstance(HINSTANCE);
	
	virtual void startLocalGame() override;

	protected:
	HINSTANCE hinst;
};

#endif
