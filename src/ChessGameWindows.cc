#include "ChessGameWindows.h"

ChessGameWindows::ChessGameWindows(View* a, View* b, HINSTANCE h, HICON hi) : ChessGame(a, b) 
{
	hinst = h;
	WinView* wv = new WinView(game, hinst);
	wv->setHIcon(hi);
	hIcon = hi;
	whitePlayer = wv;
	
	blackPlayer = whitePlayer;
	game->setStartingBoard(true);
	
	Log::delViewById(0); // to prevent double logging to the same view, since in local game w/b are the same.
}

ChessGameWindows::~ChessGameWindows() {}
	
void ChessGameWindows::runLocalGame()
{
	while(true)
	{
		whitePlayer->update();
		if(!localGameloop())
			break;
	}
}