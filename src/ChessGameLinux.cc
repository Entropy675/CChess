
#include "ChessGameLinux.h"

ChessGameLinux::ChessGameLinux(View* a, View* b) : ChessGame(a, b) {}

ChessGameLinux::~ChessGameLinux() {}

void ChessGameLinux::runLocalGame()
{
	whitePlayer = new NcView(game);
	blackPlayer = whitePlayer;
	game->setStartingBoard(true);
	
	whitePlayer->update();
	whitePlayer->print("");
	whitePlayer->print("Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.");
	whitePlayer->print("Input a command with \"[a-h][1-8] [a-h][1-8]\", more options will be added later.");
	Log::delViewById(0); // to prevent double logging to the same view, since in local game w/b are the same.
	
	int run = 1;
	
	while(run)
		run = localGameloop();
}