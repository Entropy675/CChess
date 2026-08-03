#include "ChessGame.h"

using namespace std;

ChessGame::ChessGame(View* wp, View* bp) : whitePlayer(wp), blackPlayer(bp)
{
	game = new Board();
	if(wp != nullptr)
	{		
		wp->subscribeToGame(game);
		Log::addView(wp);
	}
	
	if(bp != nullptr)
	{
		bp->subscribeToGame(game);
		Log::addView(bp);
	}
}

ChessGame::~ChessGame()
{
	if(whitePlayer != nullptr)
		delete whitePlayer;
	
	if(whitePlayer == blackPlayer)
	{
		whitePlayer = nullptr;
		blackPlayer = nullptr;
		delete game;
		return;
	}
	
	whitePlayer = nullptr;
	
	if(blackPlayer != nullptr)
		delete blackPlayer;
	blackPlayer = nullptr;
	
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

void ChessGame::localGameloop()
{
    Log log(1);
    bool redraw;

    while(true)
    {
        redraw = true;
        string uinp;
        whitePlayer->userInput(uinp);

        ChessStatus promotionAsk = ChessStatus::FAIL;
        
        // positions, moving from p1 to p2
        Pos p1(0,0), p2(0,0);
        
        regex pattern("[a-h][1-8] [a-h][1-8]");
        if(regex_match(uinp, pattern))
        {
            p1.setX(uinp[0] - 'a'); 
            p1.setY(8 - (uinp[1] - '0')); 
        
            p2.setX(uinp[3] - 'a');
            p2.setY(8 - (uinp[4] - '0'));
        }
    
        regex pattern1("[a-h][1-8][a-h][1-8]");
        if(regex_match(uinp, pattern1))
        {
            p1.setX(uinp[0] - 'a'); 
            p1.setY(8 - (uinp[1] - '0'));

            p2.setX(uinp[2] - 'a');
            p2.setY(8 - (uinp[3] - '0'));
        }
        
        regex pattern2("[kqrbnp][a-h][1-8]");
        if(regex_match(uinp, pattern2))
        {
            // TODO: piece type move logic
        }
        
        bool moveAttempted = (p1 != p2);
        bool moveSuccessful = false;

        if(moveAttempted)
        {			
            Piece* randomPiece = (*game)[p1.getX()][p1.getY()];
            
            // ==========================================
            // LOG LEVEL 2: Pre-move "Extra Stuff"
            // ==========================================
            log.setLogLevel(2);
            log.append("Pre move:  " + game->toFENString() + "\n");
            log.append("Attempt: " + p1.toString() + " " + p2.toString() + "\n");
            if(randomPiece != nullptr)
                log.append(randomPiece->toString() + "\n");
            
            // ****Move piece on board***
            promotionAsk = game->movePiece(p1, p2); 
            
            log.append("CHESSSTATUS: " + getChessStatusString(promotionAsk) + "\n");
            
            // Determine if the move actually succeeded
            moveSuccessful = (promotionAsk != ChessStatus::FAIL); 
            
            // ==========================================
            // LOG LEVEL 1: Successful Move Log
            // ==========================================
            if(moveSuccessful)
            {
                log.setLogLevel(1);
                log.append("Move: " + std::string{randomPiece->getCharacter()} + p1.toString() + " -> " + p2.toString());
                log.flush();
            }
        }

        // Handle UI commands (no logging needed)
        if(uinp == string("tg"))
            whitePlayer->toggleSize();
        else if(uinp == string("exit"))
            break;
        else if(uinp == string("new") || uinp == string("restart"))
            game->setStartingBoard(true);
        
        // Handle Promotion
        if(promotionAsk == ChessStatus::PROMOTE)
        {
            bool validInput = false;
            while(!validInput)
            {
                uinp = "";
                whitePlayer->update();
                whitePlayer->print(""); 
                whitePlayer->print("");
                whitePlayer->print("Pawn can be promoted! Input promotion (Q, N, R, B). ");
                whitePlayer->userInput(uinp);
                
                validInput = game->registerPromotion(uinp);
                
                // ==========================================
                // LOG LEVEL 2: Promotion "Extra Stuff"
                // ==========================================
                log.setLogLevel(2);
                log.append("Checking promotion... ");
                if(validInput)
                    log.append("Valid!");
                else
                    log.append("Invalid :(");
                log.flush();
            }
        }
        
        // ==========================================
        // LOG LEVEL 2: Post-move "Extra Stuff"
        // ==========================================
        if(moveSuccessful)
        {
            log.setLogLevel(2);
            log.append("Post move: " + game->toFENString() + "\n");
            log.append(mergeStrings(
                ("Attack map:\n" + mergeStrings("W" + game->getWhiteAttackMap().toString(false), "B" + game->getBlackAttackMap().toString(false) + "\n"))
                ,("\t\t\tMove map:\n" + mergeStrings("W" + game->getWhiteMoveMap().toString(false), "B" + game->getBlackMoveMap().toString(false)))));
            log.flush();
        }
        
        // Reset log level to default before rendering
        log.setLogLevel(1);

        if(redraw)
        {
            whitePlayer->update();
            updateAllSpectators();
        }
    }

    whitePlayer->update();
    updateAllSpectators();
}
