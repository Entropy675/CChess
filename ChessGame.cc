#include "ChessGame.h"

using namespace std;

ChessGame::ChessGame()
{
	game = new Board();
	view = new NcView(game);
}

ChessGame::~ChessGame()
{
	delete game;
	delete view;
}

void ChessGame::startGame()
{
	game->setStartingBoard(true);
	view->update();

	view->printAt(20, 0, "Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.");
	view->printAt(21, 0, "Input a command with \"[a-h][1-8] [a-h][1-8]\", more options will be added later.");

	bool redraw;

	while(true)
	{

		redraw = true;

		string uinp;
		view->userInput(uinp);

		//addstr(uinp.c_str());

		// for valid input, must be of format "c# c#", where c = char in "abcdefgh"
		// could also support p = kqrnbp in format "pc#", where only one valid move can go there.
		// could also support "c#" where only one valid move exists (this is cringe but completely doable)

		regex pattern("[a-h][1-8] [a-h][1-8]"); // lets just use regex

		if(regex_match(uinp, pattern))
		{
			// this is a valid input
			Pos p1, p2;

			p1.setX(uinp[0] - 'a'); // a
			p1.setY(8 - (uinp[1] - '0')); // 1 -> 0

			p2.setX(uinp[3] - 'a');
			p2.setY(8 - (uinp[4] - '0'));

			game->movePiece(p1, p2); // has access to board, has access to both pieces
		}

		regex pattern2("[a-h][1-8]"); // lets just use regex

		if(regex_match(uinp, pattern2))
		{
			// this is a valid input for single location given (only one possible valid move)
			// requires full piece functionality
		}

		if(uinp == string("tg"))
		{
			view->toggleSize();
			refresh();
		}

		else if(uinp == string("exit"))
			break;

		if(redraw)
		{
			view->update();
			refresh();
		}
	}

	refresh();
}
