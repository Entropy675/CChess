#ifndef CHESSGAMELINUX_H
#define CHESSGAMELINUX_H

#include <string>
#include <cstring>
#include <regex>
#include <iostream>
#include <vector>

#include "Board.h"
#include "View.h"
#include "Log.h"
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
