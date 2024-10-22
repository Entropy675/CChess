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
