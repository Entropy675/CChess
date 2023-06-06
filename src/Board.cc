#include "Board.h"
#include <cctype>

#include "piece_behav/PawnMove.h"
#include "piece_behav/KingMove.h"
#include "piece_behav/KnightMove.h"
#include "piece_behav/PlusMove.h"
#include "piece_behav/CrossMove.h"



Board::Board() 
	: whiteKing(nullptr), whiteCheck(false), whiteCastleKS(true), whiteCastleQS(true), blackKing(nullptr), blackCheck(false), blackCastleKS(true), blackCastleQS(true), 
	  enPassantActive(false), previousPiece(nullptr), whitePerspective(true), whiteTurn(true), halfmoveCount(0), turnCountFEN(1), moveCount(0)
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

// Overload [] for individual rows, chains with proxy to make [][] operation possible.
Board::Proxy Board::operator[](int row) const
{
	return Proxy(gameBoard[row]);
}

// Overload () for access individual elements.
Piece* Board::operator()(int row, int col) const
{
	return gameBoard[row][col];
}
	
Piece* Board::operator[](Pos p) const
{
	return (*this)(p[0], p[1]);
}
	
// Refactor this entire function using the new 
/*
	Bitboard getWhiteAttackMap(const Piece& p, Pos* to) const;
	Bitboard getBlackAttackMap(const Piece& p, Pos* to) const;
	Bitboard getWhiteMoveMap(const Piece& p, Pos* to) const;
	Bitboard getBlackMoveMap(const Piece& p, Pos* to) const;
*/
// functions.
ChessStatus Board::movePiece(Pos a, Pos b) // move from a to b if valid on this piece
{

	if(getPiece(a) == nullptr || getPiece(a)->isWhite() != whiteTurn)
		return ChessStatus::FAIL;

	Log log(2);
	log.append(std::string("pre checks: ")  + (whiteCheck ? "WcurrentCheck" : "") + ", " + (blackCheck ? "BcurrentCheck" : "\n"));
	
	ChessStatus returnChessStatus = getPiece(a)->move(b); // ***attempt move on piece***
	
	if(returnChessStatus == ChessStatus::PAWNMOVE || returnChessStatus == ChessStatus::PROMOTE)
		halfmoveCount = 0;
	
	bool prevWhiteCheck = whiteCheck;
	bool prevBlackCheck = blackCheck;
	Piece* ifSuccessKill = nullptr;
	int tempHalfmoveCount = halfmoveCount;
	
	if(returnChessStatus != ChessStatus::FAIL) // FAIL is only case where nothing happen
	{
		// Update the halfmove count and kill the piece according to rules (or fail if same color)
		if(gameBoard[b.getX()][b.getY()] != nullptr)
		{
			if(gameBoard[b.getX()][b.getY()]->isWhite() == getPiece(a)->isWhite())
				return ChessStatus::FAIL;
			
			ifSuccessKill = gameBoard[b.getX()][b.getY()];
			tempHalfmoveCount = 0;
		}
		else if(returnChessStatus != ChessStatus::PAWNMOVE && returnChessStatus != ChessStatus::PROMOTE)
			tempHalfmoveCount++;
		
		// ? -- Preposition: a function that returns the attack/move bit board of the game with a piece moved to a different pos.
		// Use that function to make this one make way more sense please...
		
		// ***Move Piece***
		gameBoard[b.getX()][b.getY()] = getPiece(a);
		clearPiece(a);
		updateMaps(); // now the kings know if they are under attack
		
		// update white & black checks 
		if(blackAttackMap[whiteKing->getPos()])
			whiteCheck = true;
		else
			whiteCheck = false;
		
		if(whiteAttackMap[blackKing->getPos()])
			blackCheck = true;
		else
			blackCheck = false;
		
		log.append(std::string("post checks: ")  + (whiteCheck ? "WcurrentCheck" : "") + ", " + (blackCheck ? "BcurrentCheck" : "\n"));
		
		if((whiteCheck && getPiece(b)->isWhite()) || (blackCheck && !getPiece(b)->isWhite()))
		{
			log.append("***undoing move***\n");
			// ***Undo Move***
			gameBoard[a.getX()][a.getY()] = getPiece(b);
			gameBoard[b.getX()][b.getY()] = ifSuccessKill;
			updateMaps();
			
			// **Reset Checks**
			whiteCheck = prevWhiteCheck;
			blackCheck = prevBlackCheck;
			
			return ChessStatus::FAIL;
		}
		
		if(returnChessStatus != ChessStatus::PROMOTE)
		{
			if(!whiteTurn)
				turnCountFEN++;
			moveCount++;
			whiteTurn = !whiteTurn;
			returnChessStatus = ChessStatus::SUCCESS;
		}

		if(ifSuccessKill != nullptr)
			ifSuccessKill->die();
		
		halfmoveCount = tempHalfmoveCount;
		
		log.append("SUCCESS.\n");
		previousPiece = getPiece(b); // keeps track of last piece moved, for promotion
	}

	return returnChessStatus; // if success, returns PROMOTE or SUCCESS
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
	FENs += getEnPassantBoardPosFEN();
	
	FENs += " ";
	FENs += std::to_string(halfmoveCount);
	FENs += " ";
	FENs += std::to_string(turnCountFEN);
	
	return FENs;
}
	
	// CHANGE HOW THIS WORKS!!! any pawn that moves up 2
std::string Board::getEnPassantBoardPosFEN() const
{
	Log log(2);
	
	
	
	if(enPassantActive)
	{		
		log.append("enPassantActive!!! " + std::to_string(whitePieces->size()) + "\n");
		for(long unsigned int i = 0; i < whitePieces->size(); i++)
		{
			const PawnMove* tmp = whitePieces->at(i)->getPawnBehaviour();
			
			if(tmp != nullptr)
			{
				const Piece* enPassantTarget = tmp->getEnPassantTarget();
				if(enPassantTarget != nullptr)
					return enPassantTarget->getBoardPos();
			}

			tmp = blackPieces->at(i)->getPawnBehaviour();
			if(tmp != nullptr)
			{
				const Piece* enPassantTarget = tmp->getEnPassantTarget();
				if(enPassantTarget != nullptr)
					return enPassantTarget->getBoardPos();
			}
		}
	}
	
	return "-";
}

void Board::disableCheck()
{
	whiteCheck = false;
	blackCheck = false;
}

bool Board::isCheckOnBoard() const
{
	return whiteCheck || blackCheck;
}
	
	
bool Board::registerPromotion(std::string& s)
{
	// mr hacker even if you did somehow call this, if you are playing an online game it works on a consensus system - you would just be resynced to what it was before :)
	char input = promotionMatchChar(s);
	Log log(2);
	
	std::string outstring = "promotionMatchChar? ";
	outstring += input;
	outstring += " previousPiece: " + ((previousPiece == nullptr) ? "NULL!" : previousPiece->toString());
	
	log.append(outstring);
	
	// {R, N, B, Q, P} -> {Rook, Knight, Bishop, Queen, Pawn}
	if(input == '\0' || previousPiece == nullptr)
		return false;
	
	switch(std::tolower(input))
	{
		case 'r':
			previousPiece->promote('r');
			break;
		case 'n':
			previousPiece->promote('n');
			break;
		case 'b':
			previousPiece->promote('b');
			break;
		case 'q':
			previousPiece->promote('q');
			break;	
		default:
			return false;
	}
	
	previousPiece = nullptr;
	if(!whiteTurn)
		turnCountFEN++;
	moveCount++;
	whiteTurn = !whiteTurn;
	return true;
}

char Board::promotionMatchChar(std::string& s)
{
	const char* charArr = "rnbq"; // cant promote to pawn or king
	for(long unsigned int i = 0; i < sizeof(charArr); i++) // sizeof gives byte size, chars are all 1 byte though
		if(std::tolower(s[0]) == std::tolower(charArr[i]))
			return charArr[i];
	return '\0';
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
			bool king = false;

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
				king = true;
			}
			else if (y == 1 || y == MAX_ROW_COL-2)
			{
				// Pawn
				gameBoard[x][y] = new Piece(Pos(x,y), 'P', (y == 1) ? !startingColor : startingColor, this);
				gameBoard[x][y]->addBehav(new PawnMove());
			}


			if(y == 0)
			{
				blackPieces->push_back(gameBoard[x][y]);
				if (king)
					blackKing = gameBoard[x][y];
			}
			else if(y == MAX_ROW_COL-1)
			{
				whitePieces->push_back(gameBoard[x][y]);
				if (king)
					whiteKing = gameBoard[x][y];
			}
			
		}
	}

	for(int i = 0; i < MAX_ROW_COL; i++)
	{
		blackPieces->push_back(gameBoard[i][1]);
		whitePieces->push_back(gameBoard[i][MAX_ROW_COL-2]);
	}
	
	updateMaps();
}

void Board::updateMaps()
{
	whiteAttackMap.clear();
	blackAttackMap.clear();
	whiteMoveMap.clear();
	blackMoveMap.clear();
	
	for(long unsigned int i = 0; i < whitePieces->size(); i++)
	{
		whiteAttackMap = whiteAttackMap | whitePieces->at(i)->validCaptures();
		whiteMoveMap = whiteMoveMap | whitePieces->at(i)->validMoves();
	}
	
	for(long unsigned int i = 0; i < blackPieces->size(); i++)
	{
		blackAttackMap = blackAttackMap | blackPieces->at(i)->validCaptures();	
		blackMoveMap = blackMoveMap | blackPieces->at(i)->validMoves();
	}
}

const Piece& Board::getWhiteKing() const
{
	return *whiteKing;
}

const Piece& Board::getBlackKing() const
{
	return *blackKing;
}

const Bitboard& Board::getWhiteAttackMap() const
{
	return whiteAttackMap;
}

const Bitboard& Board::getBlackAttackMap() const
{
	return blackAttackMap;
}
	
const Bitboard& Board::getWhiteMoveMap() const
{
	return whiteMoveMap;
}

const Bitboard& Board::getBlackMoveMap() const
{
	return blackMoveMap;
}


Bitboard Board::getWhiteAttackMap(const Piece& p, Pos* to) const
{
	Bitboard tmp;
	for(long unsigned int i = 0; i < whitePieces->size(); i++)
		if(whitePieces->at(i) != &p)
			tmp = tmp | whitePieces->at(i)->validCaptures();
	
	tmp = tmp | p.validCaptures(to);
	return tmp;
}

Bitboard Board::getBlackAttackMap(const Piece& p, Pos* to) const
{
	Bitboard tmp;
	for(long unsigned int i = 0; i < blackPieces->size(); i++)
		if(blackPieces->at(i) != &p)
			tmp = tmp | blackPieces->at(i)->validCaptures();
	
	tmp = tmp | p.validCaptures(to);
	return tmp;
}

Bitboard Board::getWhiteMoveMap(const Piece& p, Pos* to) const
{
	Bitboard tmp;
	for(long unsigned int i = 0; i < whitePieces->size(); i++)
		if(whitePieces->at(i) != &p)
			tmp = tmp | whitePieces->at(i)->validMoves();
	
	tmp = tmp | p.validMoves(to);
	return tmp;
}

Bitboard Board::getBlackMoveMap(const Piece& p, Pos* to) const
{
	Bitboard tmp;
	for(long unsigned int i = 0; i < blackPieces->size(); i++)
		if(blackPieces->at(i) != &p)
			tmp = tmp | blackPieces->at(i)->validMoves();
	
	tmp = tmp | p.validMoves(to);
	return tmp;
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

bool Board::isWhitePerspective() const
{
	return whitePerspective;
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
