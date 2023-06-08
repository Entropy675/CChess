#include "ChessGameWindows"

ChessGameWindows::ChessGameWindows(View* a, View* b) : ChessGame(a, b) {}

void ChessGameWindows::setHInstance(HINSTANCE h)
{
	hinst = h;
}

ChessGameWindows::~ChessGameWindows() {}
	
void ChessGameWindows::startLocalGame()
{
	whitePlayer = new WinView(game, hinst);
	blackPlayer = whitePlayer;
	game->setStartingBoard(true);
	
	whitePlayer->update();
	whitePlayer->print("");
	whitePlayer->print("Don't really know what this looks like yet...");
	Log::delViewById(0); // to prevent double logging to the same view, since in local game w/b are the same.
	
	localGameloop()
}