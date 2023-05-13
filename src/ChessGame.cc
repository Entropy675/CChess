#include "ChessGame.h"
#include "NcView.h"
using namespace std;

ChessGame::ChessGame(View* wp, View* bp) : whitePlayer(wp), blackPlayer(bp)
{
	game = new Board();
	wp->subscribeToGame(game);
	bp->subscribeToGame(game);
	Log::addView(wp);
	Log::addView(bp);
}

ChessGame::~ChessGame()
{
	delete game;
}

void ChessGame::addView(View* view)
{
	otherViews.push_back(view);
	Log::addView(view);
}

void ChessGame::updateAllSpectators()
{
	for(long unsigned int i = 0; i < otherViews.size(); i++)
		otherViews[i]->update();
}
	
// for this ncurses implementation we will assume that the whitePlayer = blackPlayer (local machine)
void ChessGame::startLocalNcursesGame()
{
	game->setStartingBoard(true);
	
	whitePlayer->update();
	whitePlayer->print("Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.");
	whitePlayer->print("Input a command with \"[a-h][1-8] [a-h][1-8]\", more options will be added later.");
	Log::delViewById(0); // to prevent double logging to the same view, since in local the are the same.
	
	bool redraw;

	while(true)
	{

		redraw = true;

		string uinp;
		whitePlayer->userInput(uinp);

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

		regex pattern2("[kqrbnp][a-h][1-8]"); // lets just use regex

		if(regex_match(uinp, pattern2))
		{
			// this is a valid input for single location given (only one possible valid move)
			// TODO: check each valid move that leads to this square, if there are more then one then don't do anything
		}

		if(uinp == string("tg"))
			whitePlayer->toggleSize();

		else if(uinp == string("exit"))
			break;
		

		if(promotionAsk == ChessStatus::PROMOTE)
		{
			bool validInput = false;
			while(!validInput)
			{
				uinp = "";
				
				whitePlayer->update();
				whitePlayer->print("Pawn can be promoted! Input promotion (Q, N, R, B). ");
				whitePlayer->userInput(uinp);
				
				validInput = game->registerPromotion(uinp);
				
				Log log(1);
				log.append("Checking promotion... : ");
				if(validInput)
					log.append("Valid!");
				else
					log.append("Invalid :(");
				log.flush();
			}
		}


		if(redraw)
		{
			whitePlayer->update();
			updateAllSpectators();
		}
	}

	whitePlayer->update();
	updateAllSpectators();
}
