#include "Board.h"

#include "pieces/Pawn.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Knight.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"



Board::Board() : refreshEPPawns(false), turnCount(0)
{
	whitePieces = new std::vector<Piece*>;
	blackPieces = new std::vector<Piece*>;
}

Board::~Board()
{	
	// board cleans up the pieces it holds
	for(long unsigned int i = 0; i < whitePieces->size(); i++)
		delete whitePieces->at(i); // never ever remove pieces from this, just set them dead when they die
		
	for(long unsigned int i = 0; i < blackPieces->size(); i++)
		delete blackPieces->at(i);		
	
	delete whitePieces;
	delete blackPieces;
}

bool Board::isWhiteTurn() const
{
	return whiteTurn;
}

Piece* Board::getPiece(Pos a) const
{
	return gameBoard[a.getX()][a.getY()];
}

void Board::clearPiece(Pos a)
{
	gameBoard[a.getX()][a.getY()] = nullptr;
}

int Board::getTurn() const
{
	return turnCount;
}

std::vector<Piece*>* Board::getWhitePieces() const
{
	return whitePieces;
}

std::vector<Piece*>* Board::getBlackPieces() const
{
	return blackPieces;
}

void Board::movePiece(Pos a, Pos b) // move from a to b if valid on this piece
{
	
	if(getPiece(a) == nullptr || getPiece(a)->isWhite() != whiteTurn)
		return;
		
	NcLog log(1); // basic log level

	if(getPiece(a)->move(b))
	{	
		if(gameBoard[b.getX()][b.getY()] != nullptr)
			gameBoard[b.getX()][b.getY()]->die();
			
		gameBoard[b.getX()][b.getY()] = getPiece(a);
		clearPiece(a);
		whiteTurn = !whiteTurn;
		turnCount++;
		log.append("tc: " + std::to_string(turnCount));
	}
	
	log.flush(); // log all movement comments to screen.
}

void Board::setStartingBoard(bool startingColor)
{
	// place pieces in their starting positions,
	// populate the vectors corresponding to the black/white pieces.
	
	
	whiteTurn = startingColor;
	
	for(int x = 0; x < MAX_ROW_COL; x++)
	{
		for(int y = 0; y < MAX_ROW_COL; y++)
		{
			gameBoard[x][y] = nullptr;
			
			if((x == 0 || x == MAX_ROW_COL-1) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[x][y] = new Rook(Pos(x,y), (y == 0) ? !startingColor : startingColor, this);
			else if ((x == 1 || x == MAX_ROW_COL-2) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[x][y] = new Knight(Pos(x,y), (y == 0) ? !startingColor : startingColor, this);
			else if ((x == 2 || x == MAX_ROW_COL-3) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[x][y] = new Bishop(Pos(x,y), (y == 0) ? !startingColor : startingColor, this);
			else if ((x == 3) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[x][y] = new Queen(Pos(x,y), (y == 0) ? !startingColor : startingColor, this);
			else if ((x == 4) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[x][y] = new King(Pos(x,y), (y == 0) ? !startingColor : startingColor, this);
			else if (y == 1 || y == MAX_ROW_COL-2)
				gameBoard[x][y] = new Pawn(Pos(x,y), (y == 1) ? !startingColor : startingColor, this);
			

			if(y == 0)
				blackPieces->push_back(gameBoard[x][y]);
			else if(y == MAX_ROW_COL-1)
				whitePieces->push_back(gameBoard[x][y]);
		
		}
	}
	
	for(int i = 0; i < MAX_ROW_COL; i++)
	{
		blackPieces->push_back(gameBoard[i][1]);
		whitePieces->push_back(gameBoard[i][MAX_ROW_COL-2]);
	}
}





