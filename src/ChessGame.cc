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
	whitePlayer->print("");
	whitePlayer->print("Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.");
	whitePlayer->print("Input a command with \"[a-h][1-8] [a-h][1-8]\", more options will be added later.");
	Log::delViewById(0); // to prevent double logging to the same view, since in local game w/b are the same.

	Log log(1);
	bool redraw;

	while(true)
	{

		redraw = true;

		string uinp;
		whitePlayer->userInput(uinp);

		//addstr(uinp.c_str());

		// for valid input, must be of format "c# c#", where c = char in "abcdefgh"
		// could also support p = kqrnbp in format "pc#", where only one valid move can go there.
		// (requires some assumptions about where the pieces are in the array & some validity checks)
		// (could also just scan through all pieces, there are only 16... its not really slow.)

		ChessStatus promotionAsk = ChessStatus::FAIL;
		log.setLogLevel(2);
		log.append("Pre move:  " + game->toFENString() + "\n");
		log.setLogLevel(1);
		
		regex pattern("[a-h][1-8] [a-h][1-8]");
		
		if(regex_match(uinp, pattern))
		{
			// this is a valid input
			Pos p1, p2;

			p1.setX(uinp[0] - 'a'); // ['a', 'b', 'c'] -> [0, 1, 2]
			p1.setY(8 - (uinp[1] - '0')); // ['8', '7', '6'] -> [0, 1, 2]

			Piece* randomPiece = (*game)[p1.getX()][p1.getY()];
		
			p2.setX(uinp[3] - 'a');
			p2.setY(8 - (uinp[4] - '0'));
			
			log.append("Attempt: " + p1.toString() + " " + p2.toString() + "\n");
			//log.append("game->movePiece(Pos" + p1.toString() + ", Pos" + p2.toString() + ");\n"); 
				
			if(randomPiece != nullptr)
				log.append(randomPiece->toString() + "\n");
			promotionAsk = game->movePiece(p1, p2); // ****Move piece on board***
			
			log.append("CHESSSTATUS: " + getChessStatusString(promotionAsk) + "\n");
		}

		regex pattern2("[kqrbnp][a-h][1-8]");

		if(regex_match(uinp, pattern2))
		{
			// this is a valid input for single location given (only one possible valid move)
			// TODO: check each valid move that leads to this square, if there are more then one then don't do anything
		}

		if(uinp == string("tg"))
			whitePlayer->toggleSize();

		else if(uinp == string("exit"))
			break;
		
		// if move was a promotion (which also means valid)...
		if(promotionAsk == ChessStatus::PROMOTE)
		{
			bool validInput = false;
			while(!validInput)
			{
				uinp = "";
				
				whitePlayer->update();
				whitePlayer->print(""); // get the write header to the same position as the bar 
				whitePlayer->print("");
				whitePlayer->print("Pawn can be promoted! Input promotion (Q, N, R, B). ");
				whitePlayer->userInput(uinp);
				
				validInput = game->registerPromotion(uinp);
				
				log.append("Checking promotion... ");
				if(validInput)
					log.append("Valid!");
				else
					log.append("Invalid :(");
				log.flush();
			}
		}
		
		
		log.append("Post move: " + game->toFENString() + "\n");
		log.append(mergeStrings(
			("Attack map:\n" + mergeStrings("W" + game->getWhiteAttackMap().toString(false), "B" + game->getBlackAttackMap().toString(false) + "\n"))
			,("\t\t\tMove map:\n" + mergeStrings("W" + game->getWhiteMoveMap().toString(false), "B" + game->getBlackMoveMap().toString(false)))));
		//log.append(game->getWhiteAttackMap().toString());
		log.flush();


		if(redraw)
		{
			whitePlayer->update();
			updateAllSpectators();
		}
	}

	whitePlayer->update();
	updateAllSpectators();
}
