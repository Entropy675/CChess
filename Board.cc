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

bool Board::isWhiteTurn()
{
	return whiteTurn;
}

Piece* Board::getPiece(Pos a)
{
	return gameBoard[a.getX()][a.getY()];
}

void Board::clearPiece(Pos a)
{
	gameBoard[a.getX()][a.getY()] = nullptr;
}

void Board::movePiece(Pos a, Pos b) // move from a to b if valid on this piece
{
	
	if(getPiece(a) == nullptr || getPiece(a)->isWhite() != whiteTurn)
		return;
		
	NcLog log;

	if(getPiece(a)->move(b))
	{	
		if(gameBoard[b.getX()][b.getY()] != nullptr)
			gameBoard[b.getX()][b.getY()]->die();
			
		gameBoard[b.getX()][b.getY()] = getPiece(a);
		clearPiece(a);
		whiteTurn = !whiteTurn;
		turnCount++;
		log.add("tc: " + std::to_string(turnCount));
	}
	
	log.post(1); // log all movement comments to screen.
}

int Board::getTurn()
{
	return turnCount;
}

void Board::setStartingBoard(bool startingColor)
{
	// place pieces in their starting positions,
	// populate the vectors corresponding to the black/white pieces.
	
	/*whitePieces
	blackPieces
	*/
	
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
	
	
	/* old method
	// top pieces
	gameBoard[0][0] = new Rook(Pos(0,0), !startingColor, this);
	gameBoard[0][1] = new Knight(Pos(0,1), !startingColor, this);
	gameBoard[0][2] = new Bishop(Pos(0,2), !startingColor, this);
	gameBoard[0][3] = new Queen(Pos(0,3), !startingColor, this);
	gameBoard[0][4] = new King(Pos(0,4), !startingColor, this);
	gameBoard[0][5] = new Bishop(Pos(0,5), !startingColor, this);
	gameBoard[0][6] = new Knight(Pos(0,6), !startingColor, this);
	gameBoard[0][7] = new Rook(Pos(0,7), !startingColor, this);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
		gameBoard[1][i] = new Pawn(Pos(1,i), !startingColor, this);
		
	// bottom pieces
	gameBoard[MAX_ROW_COL-1][0] = new Rook(Pos(MAX_ROW_COL-1,0), startingColor, this);
	gameBoard[MAX_ROW_COL-1][1] = new Knight(Pos(MAX_ROW_COL-1,1), startingColor, this);
	gameBoard[MAX_ROW_COL-1][2] = new Bishop(Pos(MAX_ROW_COL-1,2), startingColor, this);
	gameBoard[MAX_ROW_COL-1][3] = new Queen(Pos(MAX_ROW_COL-1,3), startingColor, this);
	gameBoard[MAX_ROW_COL-1][4] = new King(Pos(MAX_ROW_COL-1,4), startingColor, this);
	gameBoard[MAX_ROW_COL-1][5] = new Bishop(Pos(MAX_ROW_COL-1,5), startingColor, this);
	gameBoard[MAX_ROW_COL-1][6] = new Knight(Pos(MAX_ROW_COL-1,6), startingColor, this);
	gameBoard[MAX_ROW_COL-1][7] = new Rook(Pos(MAX_ROW_COL-1,7), startingColor, this);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
		gameBoard[MAX_ROW_COL-2][i] = new Pawn(Pos(MAX_ROW_COL-2,i), startingColor, this);
	*/
}





