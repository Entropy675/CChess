#include "Board.h"
#include <cctype>

#include "piece_behav/PawnMove.h"
#include "piece_behav/KingMove.h"
#include "piece_behav/KnightMove.h"
#include "piece_behav/PlusMove.h"
#include "piece_behav/CrossMove.h"



Board::Board() 
	: whiteCastleKS(true), whiteCastleQS(true), blackCastleKS(true), blackCastleQS(true), 
	  enPassantActive(false), promotePiece(nullptr), whitePerspective(true), whiteTurn(true), halfmoveCount(0), turnCountFEN(1), moveCount(0)
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

int Board::getTurnFEN() const
{
	return turnCountFEN;
}

int Board::getMoves() const
{
	return moveCount;
}
	
std::vector<Piece*>* Board::getWhitePieces() const
{
	return whitePieces;
}

std::vector<Piece*>* Board::getBlackPieces() const
{
	return blackPieces;
}

void Board::epActivate()
{
	enPassantActive = true;
}

void Board::epDeactivate()
{
	enPassantActive = false;
}

bool Board::isEnpassantOnBoard() const
{
	return enPassantActive;
}

std::string Board::toFENString() const
{
	std::string FENs = "";
	int emptySquares = 0;
	
	for(int y = 0; y < MAX_ROW_COL; y++) // each row
	{
		for(int x = 0; x < MAX_ROW_COL; x++)
		{
			Piece* cPiece = getPiece(Pos(x,y));
			if(cPiece == nullptr)
				emptySquares++;
			else
			{
				if(emptySquares > 0)
				{
					FENs += std::to_string(emptySquares);
					emptySquares = 0;
				}
				FENs += cPiece->toFENChar();
			}
		}
		
		if(emptySquares > 0)
		{
            FENs += std::to_string(emptySquares);
            emptySquares = 0;
		}
		
		if(y != MAX_ROW_COL-1)
			FENs += "/";
	}
	
	
	FENs += " ";
	
	if(whiteTurn)
		FENs += "w";
	else
		FENs += "b";
	
	FENs += " ";
	
	if(whiteCastleKS)
		FENs += "K";
	else
		FENs += "-";
	if(whiteCastleQS)
		FENs += "Q";
	else
		FENs += "-";
	if(blackCastleKS)
		FENs += "k";
	else
		FENs += "-";
	if(blackCastleQS)
		FENs += "q";
	else
		FENs += "-";
	
	FENs += " ";
	FENs += getEnPassantBoardPos();
	
	FENs += " ";
	FENs += std::to_string(halfmoveCount);
	FENs += " ";
	FENs += std::to_string(turnCountFEN);
	
	return FENs;
}
	
std::string Board::getEnPassantBoardPos() const
{
	if(enPassantActive)
	{		
		for(long unsigned int i = whitePieces->size()/2; i < whitePieces->size(); i++)
		{
			const PawnMove* tmp = whitePieces->at(i)->getPawnBehaviour();
			if(tmp != nullptr)
			{
				const Piece* enPassantTarget = &tmp->getEnPassantTarget();
				if(enPassantTarget != nullptr)
					return enPassantTarget->getBoardPos();
			}
			
			tmp = blackPieces->at(i)->getPawnBehaviour();
			if(tmp != nullptr)
			{
				const Piece* enPassantTarget = &tmp->getEnPassantTarget();
				if(enPassantTarget != nullptr)
					return enPassantTarget->getBoardPos();
			}
		}
	}
	
	return "-";
}
	
bool Board::registerPromotion(std::string& s)
{
	// mr hacker even if you did somehow call this, if you are playing an online game it works on a consensus system - you would just be resynced to what it was before :)
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
	if(!whiteTurn)
		turnCountFEN++;
	moveCount++;
	whiteTurn = !whiteTurn;
	return true;
}

char Board::promotionMatchChar(std::string& s)
{
	const char* charArr = "rnbq"; // cant promote to pawn or king
	char temp = '\0';
	
	Log log(1);
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

	Log log(1); // basic log level
	log.append("Attempt: " + a.toString() + " " + b.toString() + "\n");
	log.append("FENs: " + toFENString() + "\n");
	
	ChessStatus returnChessStatus = getPiece(a)->move(b); // attempt move
	log.append("CHESSSTATUS in BOARD: " + getChessStatusString(returnChessStatus) + "\n");
	
	promotePiece = getPiece(a); // keeps track of previous piece moved, for promotion
	
	if(returnChessStatus == ChessStatus::PAWNMOVE || returnChessStatus == ChessStatus::PROMOTE)
		halfmoveCount = 0;
	
	if(returnChessStatus != ChessStatus::FAIL) // FAIL is only case where nothing happen
	{
		if(gameBoard[b.getX()][b.getY()] != nullptr)
		{
			gameBoard[b.getX()][b.getY()]->die();
			halfmoveCount = 0;
		}
		else if(returnChessStatus != ChessStatus::PAWNMOVE && returnChessStatus != ChessStatus::PROMOTE)
		{
			halfmoveCount++;
			log.append("\nINCREMENTING HALFMOVE: " + getChessStatusString(returnChessStatus) + "\n");
		}
		
		gameBoard[b.getX()][b.getY()] = getPiece(a);
		clearPiece(a);
		
		if(returnChessStatus != ChessStatus::PROMOTE)
		{
			if(!whiteTurn)
				turnCountFEN++;
			moveCount++;
			whiteTurn = !whiteTurn;
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
	whitePerspective = startingColor;

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
