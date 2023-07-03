#ifndef CHESSGAMELINUX_H
#define CHESSGAMELINUX_H

#include "ChessGame.h"
#include "NcView.h"

class ChessGameLinux : public ChessGame
{
	public:
	ChessGameLinux(View* = nullptr, View* = nullptr);
	~ChessGameLinux();
	virtual void startLocalGame() override;
};

#endif
