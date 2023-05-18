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
	
// only merge strings of same '/n' newline count
std::string mergeStrings(const std::string& str1, const std::string& str2) 
{
    std::string mergedString;
	std::string str2offset(str2);
	str2offset += "\n"; // (the second one needs to be offset by at least one /n)
	
	unsigned long size = str1.size() + str2.size();
	unsigned long str1c = 0;
	unsigned long str2c = 0;
	
	bool flip = false;
	while(str1c + str2c < size)
	{
		char current;
		if(flip)
			current = str1[str1c++];
		else
			current = str2offset[str2c++];
			
		if(current == '\n')
		{
			flip = !flip;
			if(flip)
			{
				mergedString += "  ";
				size += 2;
			}
			else
				mergedString += current;
		}
		else
			mergedString += current;
	}

    return mergedString;
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
		// could also support "c#" where only one valid move exists (this is cringe but completely doable)

		regex pattern("[a-h][1-8] [a-h][1-8]"); // lets just use regex
		ChessStatus promotionAsk = ChessStatus::FAIL;
		log.append("Pre move:  " + game->toFENString() + "\n");
		
		if(regex_match(uinp, pattern))
		{
			// this is a valid input
			Pos p1, p2;

			p1.setX(uinp[0] - 'a'); // a
			p1.setY(8 - (uinp[1] - '0')); // 1 -> 0

			p2.setX(uinp[3] - 'a');
			p2.setY(8 - (uinp[4] - '0'));
			
			log.append("Attempt: " + p1.toString() + " " + p2.toString() + "\n");
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
				
				log.append("Checking promotion... : ");
				if(validInput)
					log.append("Valid!");
				else
					log.append("Invalid :(");
				log.flush();
			}
		}
		
		
		log.append("Post move: " + game->toFENString() + "\n");
		log.append("Attack map:\n" + mergeStrings(game->getWhiteAttackMap().toString(), game->getBlackAttackMap().toString()));
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
