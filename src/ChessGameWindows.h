#ifndef CHESSGAMEWINDOWS_H
#define CHESSGAMEWINDOWS_H

#include "ChessGame.h"
#include "Windows.h"
#include "WinView.h"

class ChessGameWindows : public ChessGame
{
	public:
	ChessGameWindows(View* = nullptr, View* = nullptr);
	~ChessGameWindows();
	
	void setHInstance(HINSTANCE);
	
	virtual void runLocalGame() override;

	protected:
	HINSTANCE hinst;
};

#endif
