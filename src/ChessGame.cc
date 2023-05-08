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

	view->print("Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.");
	view->print("Input a command with \"[a-h][1-8] [a-h][1-8]\", more options will be added later.");

	bool redraw;
	/*
	game->movePiece(Pos(3, 6), Pos(3, 4));
	game->movePiece(Pos(4, 1), Pos(4, 3));
	game->movePiece(Pos(3, 4), Pos(4, 3));
	game->movePiece(Pos(0, 1), Pos(0, 2));
	game->movePiece(Pos(4, 3), Pos(4, 2));
	game->movePiece(Pos(0, 2), Pos(0, 3));
	game->movePiece(Pos(4, 2), Pos(4, 1));
	game->movePiece(Pos(0, 3), Pos(0, 4));
	*/
	
	/* all up two:
	game->movePiece(Pos(0, 6), Pos(0, 4));
	game->movePiece(Pos(0, 1), Pos(0, 3));
	game->movePiece(Pos(1, 6), Pos(1, 4));
	game->movePiece(Pos(1, 1), Pos(1, 3));
	game->movePiece(Pos(2, 6), Pos(2, 4));
	game->movePiece(Pos(2, 1), Pos(2, 3));
	game->movePiece(Pos(3, 6), Pos(3, 4));
	game->movePiece(Pos(3, 1), Pos(3, 3));
	game->movePiece(Pos(4, 6), Pos(4, 4));
	game->movePiece(Pos(4, 1), Pos(4, 3));
	game->movePiece(Pos(5, 6), Pos(5, 4));
	game->movePiece(Pos(5, 1), Pos(5, 3));
	game->movePiece(Pos(6, 6), Pos(6, 4));
	game->movePiece(Pos(6, 1), Pos(6, 3));
	game->movePiece(Pos(7, 6), Pos(7, 4));
	game->movePiece(Pos(7, 1), Pos(7, 3));
	*/



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
		ChessStatus promotionAsk = ChessStatus::FAIL;

		if(regex_match(uinp, pattern))
		{
			// this is a valid input
			Pos p1, p2;

			p1.setX(uinp[0] - 'a'); // a
			p1.setY(8 - (uinp[1] - '0')); // 1 -> 0

			p2.setX(uinp[3] - 'a');
			p2.setY(8 - (uinp[4] - '0'));

			promotionAsk = game->movePiece(p1, p2); // has access to board, has access to both pieces
		}

		regex pattern2("[a-h][1-8]"); // lets just use regex

		if(regex_match(uinp, pattern2))
		{
			// this is a valid input for single location given (only one possible valid move)
			// requires full piece functionality
		}

		if(uinp == string("tg"))
			view->toggleSize();

		else if(uinp == string("exit"))
			break;
		

		if(promotionAsk == ChessStatus::PROMOTE)
		{
			bool validInput = false;
			while(!validInput)
			{
				uinp = "";
				
				view->update();
				view->print("Pawn can be promoted! Input promotion (Q, N, R, B). ");
				view->userInput(uinp);
				
				validInput = game->registerPromotion(uinp);
				
				NcLog log(1);
				log.append("Checking promotion... : ");
				if(validInput)
					log.append("Valid!");
				else
					log.append("Invalid :(");
				log.flush();
			}
		}


		if(redraw)
			view->update();
	}

	view->update();
}
