#include "ChessGameWindows.h"

ChessGameWindows::ChessGameWindows(View* a, View* b) : ChessGame(a, b) {}

void ChessGameWindows::setHInstance(HINSTANCE h)
{
	hinst = h;
	whitePlayer = new WinView(game, hinst);
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