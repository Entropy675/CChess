#ifndef CHESSGAMEWINDOWS_H
#define CHESSGAMEWINDOWS_H

#include "ChessGame.h"
#include "Windows.h"
#include "WinView.h"

class ChessGameWindows
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
