#include "Board.h"
#include <cctype>

#include "piece_behav/PawnMove.h"
#include "piece_behav/KingMove.h"
#include "piece_behav/KnightMove.h"
#include "piece_behav/PlusMove.h"
#include "piece_behav/CrossMove.h"


Board::Board() : promotePiece(nullptr), turnCount(0)
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

bool Board::registerPromotion(std::string& s)
{
	
	char input = promotionMatchChar(s);
	
	// {R, N, B, Q, P} -> {Rook, Knight, Bishop, Queen, Pawn}
	if(input == '\0' || promotePiece == nullptr)
		return false;
	
	switch(std::tolower(input))
	{
		case 'r':
			promotePiece->promote('r');
			break;
		case 'n':
			promotePiece->promote('n');
			break;
		case 'b':
			promotePiece->promote('b');
			break;
		case 'q':
			promotePiece->promote('q');
			break;	
		default:
			return false;
	}
	
	promotePiece = nullptr;
	whiteTurn = !whiteTurn;
	turnCount++;
	return true;
}

char Board::promotionMatchChar(std::string& s)
{
	const char* charArr = "rnbq"; // cant promote to pawn or king
	char temp = '\0';
	
	NcLog log(1);
	for(long unsigned int i = 0; i < sizeof(charArr); i++) // sizeof gives byte size, chars are all 1 byte though
	{
		if(std::tolower(s[0]) == std::tolower(charArr[i]))
		{
			temp = charArr[i];
			break;
		}
	}
	std::string outstring = "promotionMatchChar? ";
	outstring += temp;
	log.append(outstring);
	log.flush();
	
	return temp;
}

ChessStatus Board::movePiece(Pos a, Pos b) // move from a to b if valid on this piece
{

	if(getPiece(a) == nullptr || getPiece(a)->isWhite() != whiteTurn)
		return ChessStatus::FAIL;

	NcLog log(1); // basic log level
	
	log.append("Attempt: " + a.toString() + " " + b.toString() + "\n");
	
	ChessStatus returnChessStatus = getPiece(a)->move(b); // attempt move
		
	if(returnChessStatus == ChessStatus::FAIL)
		log.append("Fail");
	if(returnChessStatus == ChessStatus::PROMOTE)
		log.append("Promote");
	if(returnChessStatus == ChessStatus::SUCCESS)
		log.append("Success");
		
	promotePiece = getPiece(a); // keeps track of previous piece moved, for promotion
	
	if(returnChessStatus != ChessStatus::FAIL) // FAIL is 0th in enum
	{
		if(gameBoard[b.getX()][b.getY()] != nullptr)
			gameBoard[b.getX()][b.getY()]->die();

		gameBoard[b.getX()][b.getY()] = getPiece(a);
		clearPiece(a);
		
		if(returnChessStatus != ChessStatus::PROMOTE)
		{
			whiteTurn = !whiteTurn;
			turnCount++;
			returnChessStatus = ChessStatus::SUCCESS;
		}
	}

	log.flush(); // log all movement comments to screen.
	return returnChessStatus; // if success, returns PROMOTE or SUCCESS
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
			{
				// Rook
				gameBoard[x][y] = new Piece(Pos(x,y), 'R', (y == 0) ? !startingColor : startingColor, this);
				gameBoard[x][y]->addBehav(new PlusMove());

			}
			else if ((x == 1 || x == MAX_ROW_COL-2) && (y == MAX_ROW_COL-1 || y == 0))
			{
				// Knight
				gameBoard[x][y] = new Piece(Pos(x,y), 'N', (y == 0) ? !startingColor : startingColor, this);
				gameBoard[x][y]->addBehav(new KnightMove());
			}
			else if ((x == 2 || x == MAX_ROW_COL-3) && (y == MAX_ROW_COL-1 || y == 0))
			{
				// Bishop
				gameBoard[x][y] = new Piece(Pos(x,y), 'B', (y == 0) ? !startingColor : startingColor, this);
				gameBoard[x][y]->addBehav(new CrossMove());
			}
			else if ((x == 3) && (y == MAX_ROW_COL-1 || y == 0))
			{
				// Queen
				gameBoard[x][y] = new Piece(Pos(x,y), 'Q', (y == 0) ? !startingColor : startingColor, this);
				gameBoard[x][y]->addBehav(new CrossMove());
				gameBoard[x][y]->addBehav(new PlusMove());
			}
			else if ((x == 4) && (y == MAX_ROW_COL-1 || y == 0))
			{
				// King
				gameBoard[x][y] = new Piece(Pos(x,y), 'K', (y == 0) ? !startingColor : startingColor, this);
				gameBoard[x][y]->addBehav(new KingMove());
			}
			else if (y == 1 || y == MAX_ROW_COL-2)
			{
				// Pawn
				gameBoard[x][y] = new Piece(Pos(x,y), 'P', (y == 1) ? !startingColor : startingColor, this);
				gameBoard[x][y]->addBehav(new PawnMove());
			}


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
