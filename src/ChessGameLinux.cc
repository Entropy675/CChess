
#include "ChessGameLinux.h"

ChessGameLinux::ChessGameLinux(View* a, View* b) : ChessGame(a, b) {}

ChessGameLinux::~ChessGameLinux() {}

void ChessGameLinux::startLocalGame()
{
	whitePlayer = new NcView(game);
	blackPlayer = whitePlayer;
	Log::addView(whitePlayer); // register the view so flush() has a sink (w == b, so add once)
	game->setStartingBoard(true);
	
	whitePlayer->update();
	whitePlayer->print("");
	whitePlayer->print("Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.");
	whitePlayer->print("Input a command with \"[a-h][1-8] [a-h][1-8]\", more options will be added later.");

	localGameloop();
}
