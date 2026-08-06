#include "Board.h"
#include <cctype>

#include "piece_behav/PawnMove.h"
#include "piece_behav/KingMove.h"
#include "piece_behav/KnightMove.h"
#include "piece_behav/PlusMove.h"
#include "piece_behav/CrossMove.h"



Board::Board() 
	: whiteKing(nullptr), whiteCheck(false), blackKing(nullptr), blackCheck(false), 
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

bool Board::isMoveValidOnKing(bool isWhiteMove, Piece& pieceMoved, Pos a, Pos b)
{
	Log log(2);
	
	bool movedIsKing = (pieceMoved.getKingBehaviour() != nullptr);
	bool validMove = true;
	Piece* temp = nullptr;
	Pos savedPos = pieceMoved.getPos(); // stateless: remember where the piece really is
	
	// ***Temp Move Piece***
	temp = gameBoard[b.getX()][b.getY()];
	gameBoard[b.getX()][b.getY()] = getPiece(a);
	clearPiece(a);
	pieceMoved.setPos(b); // so the moved piece's own attacks compute from b during the check
	if(temp != nullptr)
		temp->die();
	updateMaps(); // now when we get the attack maps the board makes sense
	
    Pos kingSquare = isWhiteMove
		? (movedIsKing ? b : getWhiteKing().getPos())
		: (movedIsKing ? b : getBlackKing().getPos());

	if(isWhiteMove)
		validMove = getBlackAttackMap()[kingSquare];
	else
		validMove = getWhiteAttackMap()[kingSquare];
	log.append(mergeStrings("B" + getBlackAttackMap().toString(false) + "\n", "W" + getWhiteAttackMap().toString(false) + "\n"));
	// ***Undo Temp Move Piece***
	gameBoard[a.getX()][a.getY()] = getPiece(b);
	gameBoard[b.getX()][b.getY()] = temp;
	pieceMoved.setPos(savedPos); // restore: the check leaves no trace
	if(temp != nullptr)
		temp->setDead(false);
	updateMaps(); 
	
	return validMove;
}

void Board::setEmptyBoard(bool whiteToMove)
{
	for(int x=0;x<MAX_ROW_COL;x++) for(int y=0;y<MAX_ROW_COL;y++) gameBoard[x][y]=nullptr;
	// delete before clearing (matches setStartingBoard); clear() alone leaks every Piece
	for(long int i = whitePieces->size() - 1; i >= 0; i--) delete whitePieces->at(i);
	for(long int i = blackPieces->size() - 1; i >= 0; i--) delete blackPieces->at(i);
	whitePieces->clear(); blackPieces->clear();
	whiteKing=nullptr; blackKing=nullptr;
	whiteTurn=whiteToMove; moveCount=0; turnCountFEN=1;
}

Piece* Board::placePiece(int x, int y, char type, bool white)
{
	Piece* p=new Piece(Pos(x,y),type,white,this);
	gameBoard[x][y]=p;
	(white?whitePieces:blackPieces)->push_back(p);
	switch(type){
		case 'R': p->addBehav(new PlusMove()); break;
		case 'N': p->addBehav(new KnightMove()); break;
		case 'B': p->addBehav(new CrossMove()); break;
		case 'Q': p->addBehav(new CrossMove()); p->addBehav(new PlusMove()); break;
		case 'K': p->addBehav(new KingMove()); if(white) whiteKing=p; else blackKing=p; break;
		case 'P': p->addBehav(new PawnMove()); break;
	}
	return p;
}

// bug: if king tries to take a piece that is attacking him that is also defended by the opponent king, the player that made the illogical move is now stuck and cannot move their king...
bool Board::castleRight(bool white, bool kingside) const
{
	// Derived from live state: king unmoved AND the home-square rook present and unmoved.
	Piece* king = white ? whiteKing : blackKing;
	if(king == nullptr || king->hasMoved())
		return false;
	int y  = white ? MAX_ROW_COL - 1 : 0;    // rank 1 (white home) / rank 8 (black home)
	int rx = kingside ? MAX_ROW_COL - 1 : 0; // h-file / a-file
	Piece* rook = gameBoard[rx][y];
	return rook != nullptr && rook->getCharacter() == 'R'
	    && rook->isWhite() == white && !rook->hasMoved();
}

ChessStatus Board::tryCastle(Pos kingSq, Pos rookSq)
{
	int y  = kingSq.getY();
	int kx = kingSq.getX();
	bool kingside = rookSq.getX() > kx;
	int kingDest = kingside ? kx + 2 : kx - 2;
	int rookDest = kingside ? kx + 1 : kx - 1;

	if(kingDest < 0 || kingDest >= MAX_ROW_COL) // guard non-standard placements
		return ChessStatus::FAIL;

	// every square strictly between king and rook must be empty
	int lo = (kx < rookSq.getX()) ? kx : rookSq.getX();
	int hi = (kx < rookSq.getX()) ? rookSq.getX() : kx;
	for(int x = lo + 1; x < hi; x++)
		if(gameBoard[x][y] != nullptr)
			return ChessStatus::FAIL;

	// the king may not start in, pass through, or land on an attacked square
	bool white = getPiece(kingSq)->isWhite();
	updateMaps(); // ensure the opponent attack map is current
	int step = kingside ? 1 : -1;
	for(int x = kx; ; x += step)
	{
		Pos sq(x, y);
		if(white ? getBlackAttackMap()[sq] : getWhiteAttackMap()[sq])
			return ChessStatus::FAIL;
		if(x == kingDest)
			break;
	}

	// perform the swap
	Piece* king = getPiece(kingSq);
	Piece* rook = getPiece(rookSq);
	clearPiece(kingSq);
	clearPiece(rookSq);
	gameBoard[kingDest][y] = king; king->setPos(Pos(kingDest, y)); king->setMoved(true);
	gameBoard[rookDest][y] = rook; rook->setPos(Pos(rookDest, y)); rook->setMoved(true);

	halfmoveCount++;
	if(!whiteTurn) turnCountFEN++;
	moveCount++;
	whiteTurn = !whiteTurn;
	updateMaps();
	whiteCheck = getBlackAttackMap()[getWhiteKing().getPos()];
	blackCheck = getWhiteAttackMap()[getBlackKing().getPos()];
	previousPiece = king;
	return ChessStatus::SUCCESS;
}

ChessStatus Board::movePiece(Pos a, Pos b) // move from a to b if valid on this piece
{

	if(getPiece(a) == nullptr || getPiece(a)->isWhite() != whiteTurn)
		return ChessStatus::FAIL;

	// Castling: an unmoved king moving toward a corner rook on its home rank,
	// entered EITHER the standard way (king two squares: e1->g1 / e1->c1) OR as
	// king-onto-rook (e1->h1 / e1->a1). Both resolve to the same corner rook and
	// go through tryCastle, which always lands the king on its standard square --
	// so the move is recorded the standard way regardless of how it was entered.
	{
		Piece* mv = getPiece(a);
		if(mv->getKingBehaviour() != nullptr && !mv->hasMoved()
		   && a.getY() == b.getY() && a.getX() != b.getX())
		{
			int dx = b.getX() - a.getX();
			int cornerX = (dx > 0) ? MAX_ROW_COL - 1 : 0; // h-file / a-file corner
			bool twoSquare = (dx == 2 || dx == -2);
			Piece* tg = getPiece(b);
			bool ontoCornerRook = (b.getX() == cornerX && tg != nullptr
			                       && tg->getCharacter() == 'R' && tg->isWhite() == mv->isWhite());
			if(twoSquare || ontoCornerRook)
			{
				Pos rookSq(cornerX, a.getY());
				Piece* rook = getPiece(rookSq);
				if(rook != nullptr && rook->getCharacter() == 'R'
				   && rook->isWhite() == mv->isWhite() && !rook->hasMoved())
					return tryCastle(a, rookSq);
			}
		}
	}

	Log log(2);
	
	// An en-passant capture kills a pawn that is NOT on the destination square, and
	// Piece::move performs that kill before the king check. Remember the victim so a
	// move rejected by isMoveValidOnKing can restore it (a rejected move must mutate nothing).
	Piece* epVictim = ((getPiece(a)->getPawnBehaviour() != nullptr) && (a.getX() != b.getX())
	                   && (gameBoard[b.getX()][b.getY()] == nullptr))
	                  ? gameBoard[b.getX()][a.getY()] : nullptr;
	
	ChessStatus returnChessStatus = getPiece(a)->move(b); // ***attempt move on piece***
	
	if(returnChessStatus != ChessStatus::FAIL) // FAIL is only case where nothing happen
	{

		log.setLogLevel(3);
		log.append("Last position for failure, fail states... \n");
		// MOVE CHECK king
		if(isMoveValidOnKing(getPiece(a)->isWhite(), *getPiece(a), a, b))
		{
			if(epVictim != nullptr && epVictim->isDead()) // EP victim was killed before this failed check; put it back
			{
				epVictim->setDead(false);
				gameBoard[epVictim->getPos().getX()][epVictim->getPos().getY()] = epVictim;
			}
			return ChessStatus::FAIL;
		}
		// at this point we can assume that the move has succeeded
		log.append("All fail states passed. \n");
		
		if(returnChessStatus != ChessStatus::PAWNMOVE && returnChessStatus != ChessStatus::PROMOTE)
			halfmoveCount++; 
		else
			halfmoveCount = 0;
		
		// Fix the halfmove count and kill the piece if piece exists
		if(gameBoard[b.getX()][b.getY()] != nullptr)
		{
			if(gameBoard[b.getX()][b.getY()]->isWhite() == getPiece(a)->isWhite())
				return ChessStatus::FAIL;
			
			gameBoard[b.getX()][b.getY()]->die();
			halfmoveCount = 0;
		}
		
		// ***Move Piece***
		Piece* mover = getPiece(a);
		gameBoard[b.getX()][b.getY()] = mover;
		clearPiece(a);
		mover->setPos(b);   // commit position here (deferred from Piece::move so a rejected move mutates nothing)
		mover->setMoved(true); // likewise commit the moved flag only on a real move (keeps castling rights honest)
		updateMaps();
		
		if(returnChessStatus != ChessStatus::PROMOTE)
		{
			if(!whiteTurn)
				turnCountFEN++;
			moveCount++;
			whiteTurn = !whiteTurn;
			returnChessStatus = ChessStatus::SUCCESS;
		}
		
		
		whiteCheck = getBlackAttackMap()[getWhiteKing().getPos()];
		blackCheck = getWhiteAttackMap()[getBlackKing().getPos()];
		
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
	
	// Standard FEN: concatenate the available rights, or a single "-" when there are none.
	std::string castle = "";
	if(castleRight(true,  true))  castle += "K";
	if(castleRight(true,  false)) castle += "Q";
	if(castleRight(false, true))  castle += "k";
	if(castleRight(false, false)) castle += "q";
	FENs += castle.empty() ? "-" : castle;
	
	FENs += " ";
	FENs += getEnPassantBoardPosFEN();
	
	FENs += " ";
	FENs += std::to_string(halfmoveCount);
	FENs += " ";
	FENs += std::to_string(turnCountFEN);
	
	return FENs;
}

bool Board::loadFEN(const std::string& fen)
{
	// Split into up to 6 space-separated fields (counters optional).
	std::string f[6]; int n = 0; std::string cur;
	for(char ch : fen)
	{
		if(ch == ' ') { if(!cur.empty() && n < 6) { f[n++] = cur; cur.clear(); } }
		else cur += ch;
	}
	if(!cur.empty() && n < 6) f[n++] = cur;
	if(n < 2) return false; // need at least board + side-to-move

	std::string boardField  = f[0];
	bool whiteToMove        = (f[1] == "w");
	std::string castleField = (n > 2) ? f[2] : "-";
	std::string epField     = (n > 3) ? f[3] : "-";
	int halfmove            = (n > 4) ? std::atoi(f[4].c_str()) : 0;
	int fullmove            = (n > 5) ? std::atoi(f[5].c_str()) : 1;

	setEmptyBoard(whiteToMove); // resets board+pieces, whiteTurn, moveCount=0, turnCountFEN=1

	// 1. pieces: ranks 8..1 (y=0..7), files a..h (x=0..7)
	int x = 0, y = 0;
	for(char ch : boardField)
	{
		if(ch == '/') { y++; x = 0; continue; }
		if(ch >= '1' && ch <= '8') { x += ch - '0'; continue; }
		if(x < MAX_ROW_COL && y < MAX_ROW_COL)
			placePiece(x, y, static_cast<char>(std::toupper(static_cast<unsigned char>(ch))),
			           std::isupper(static_cast<unsigned char>(ch)) != 0);
		x++;
	}

	// 2. castling: every piece is unmoved after placePiece (so all rights would
	//    read true). Mark the kings + corner rooks moved, then un-mark exactly the
	//    rights the FEN grants -- castleRight() derives the field from these flags.
	auto mark = [](Piece* p, bool m){ if(p) p->setMoved(m); };
	Piece* wRh = getPiece(Pos(MAX_ROW_COL-1, MAX_ROW_COL-1)); // h1
	Piece* wRa = getPiece(Pos(0,            MAX_ROW_COL-1)); // a1
	Piece* bRh = getPiece(Pos(MAX_ROW_COL-1, 0));            // h8
	Piece* bRa = getPiece(Pos(0,             0));            // a8
	mark(whiteKing,true); mark(blackKing,true);
	mark(wRh,true); mark(wRa,true); mark(bRh,true); mark(bRa,true);
	if(castleField != "-")
		for(char ch : castleField)
			switch(ch)
			{
				case 'K': mark(whiteKing,false); mark(wRh,false); break;
				case 'Q': mark(whiteKing,false); mark(wRa,false); break;
				case 'k': mark(blackKing,false); mark(bRh,false); break;
				case 'q': mark(blackKing,false); mark(bRa,false); break;
			}

	// 3. en passant. CChess encodes the double-pushed PAWN's own square here
	//    (getEnPassantBoardPosFEN returns the target pawn's getBoardPos()), not the
	//    standard square-behind -- so parse it as the pawn square directly and
	//    re-prime the side-to-move's adjacent pawns exactly as a real push would.
	enPassantActive = false;
	if(epField != "-" && epField.size() >= 2)
	{
		int ex = epField[0] - 'a';
		int ey = MAX_ROW_COL - (epField[1] - '0');
		if(ex >= 0 && ex < MAX_ROW_COL && ey >= 0 && ey < MAX_ROW_COL)
		{
			Piece* pushed = getPiece(Pos(ex, ey));
			if(pushed != nullptr && pushed->getPawnBehaviour() != nullptr)
				for(int dx = -1; dx <= 1; dx += 2)
				{
					int ax = ex + dx;
					if(ax < 0 || ax >= MAX_ROW_COL) continue;
					Piece* adj = getPiece(Pos(ax, ey));
					if(adj != nullptr && adj->getPawnBehaviour() != nullptr
					   && adj->isWhite() == whiteToMove)
						adj->getPawnBehaviour()->primeEnPassant(pushed, moveCount);
				}
		}
	}

	// 4. counters
	halfmoveCount = halfmove;
	turnCountFEN  = fullmove;
	return true;
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
			
            if(i < blackPieces->size())
            {
			    tmp = blackPieces->at(i)->getPawnBehaviour();
			    if(tmp != nullptr)
			    {
				    const Piece* enPassantTarget = tmp->getEnPassantTarget();
				    if(enPassantTarget != nullptr)
					    return enPassantTarget->getBoardPos();
			    }
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

bool Board::sideToMoveInCheck() const
{
	updateMaps();
	if(whiteTurn)
		return getBlackAttackMap()[getWhiteKing().getPos()];
	return getWhiteAttackMap()[getBlackKing().getPos()];
}

bool Board::sideToMoveHasLegalEnPassant()
{
	std::vector<Piece*>* pieces = whiteTurn ? whitePieces : blackPieces;
	for(long unsigned int i = 0; i < pieces->size(); i++)
	{
		Piece* pc = pieces->at(i);
		if(pc == nullptr || pc->isDead())
			continue;

		PawnMove* pm = pc->getPawnBehaviour();
		if(pm == nullptr || pm->getTurnToEP() != getMoves())
			continue;

		const Piece* epTarget = pm->getEnPassantTarget();
		if(epTarget == nullptr)
			continue;

		Pos from = pc->getPos();
		Pos capSq = epTarget->getPos();
		Pos to(capSq.getX(), capSq.getY() + (pc->isWhite() ? -1 : 1));

		Piece* captured = gameBoard[capSq.getX()][capSq.getY()];
		gameBoard[to.getX()][to.getY()] = pc;
		clearPiece(from);
		if(captured != nullptr)
			captured->die();
		clearPiece(capSq);
		updateMaps();

		Pos kingSq = whiteTurn ? getWhiteKing().getPos() : getBlackKing().getPos();
		bool inCheck = whiteTurn ? getBlackAttackMap()[kingSq] : getWhiteAttackMap()[kingSq];

		clearPiece(to);
		gameBoard[from.getX()][from.getY()] = pc;
		gameBoard[capSq.getX()][capSq.getY()] = captured;
		if(captured != nullptr)
			captured->setDead(false);
		updateMaps();

		if(!inCheck)
			return true;
	}
	return false;
}

bool Board::sideToMoveHasLegalMove()
{
	std::vector<Piece*>* pieces = whiteTurn ? whitePieces : blackPieces;
	for(long unsigned int i = 0; i < pieces->size(); i++)
	{
		Piece* pc = pieces->at(i);
		if(pc == nullptr || pc->isDead())
			continue;

		Pos from = pc->getPos();
		Bitboard moves = pc->validMoves();
		for(int sq = 0; sq < MAX_ARR_SIZE; sq++)
		{
			if(!moves[sq])
				continue;

			Pos to(sq % MAX_ROW_COL, sq / MAX_ROW_COL);
			Piece* dest = getPiece(to);
			if(dest != nullptr && dest->isWhite() == pc->isWhite())
				continue; // can't capture own piece — matches movePiece's guard

			if(!isMoveValidOnKing(whiteTurn, *pc, from, to))
				return true; // a king-safe legal move exists
		}
	}
	return sideToMoveHasLegalEnPassant();
}

bool Board::isCheckmate()
{
	return sideToMoveInCheck() && !sideToMoveHasLegalMove();
}

bool Board::isStalemate()
{
	return !sideToMoveInCheck() && !sideToMoveHasLegalMove();
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
	for(long unsigned int i = 0; charArr[i] != '\0'; i++) // sizeof gives byte size, chars are all 1 byte though
		if(std::tolower(s[0]) == std::tolower(charArr[i]))
			return charArr[i];
	return '\0';
}

void Board::setStartingBoard(bool startingColor)
{
	// place pieces in their starting positions,
	// populate the vectors corresponding to the black/white pieces.
	
	whitePerspective = startingColor;
	
	// Full game-state reset so setStartingBoard is a complete "new game",
	// not just piece placement. These were previously only set in the ctor,
	// so a second call (restart) would have left turn/castling/counters stale.
	whiteTurn = true;
	whiteCheck = false;
	blackCheck = false;
	enPassantActive = false;
	previousPiece = nullptr;
	halfmoveCount = 0;
	turnCountFEN = 1;
	moveCount = 0;
	
	// should be empty for the first call, for every other call the following two loops run and reset the vecs.
	for(long int i = whitePieces->size() - 1; i >= 0; i--)
	{
		delete whitePieces->at(i); 
		whitePieces->erase(whitePieces->begin() + i);
	}
	
	for(long int i = blackPieces->size() - 1; i >= 0; i--)
	{
		delete blackPieces->at(i); 
		blackPieces->erase(blackPieces->begin() + i);
	}


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

void Board::updateMaps() const
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

Bitboard Board::getWhiteAttackMap(const Piece& p, Pos* to, bool includePiecesAttacks) const
{
	return conditionalGetMap(p, to, includePiecesAttacks, [](const Piece& piece) {return piece.validCaptures();}, whitePieces); 
}

Bitboard Board::getBlackAttackMap(const Piece& p, Pos* to, bool includePiecesAttacks) const
{
	return conditionalGetMap(p, to, includePiecesAttacks, [](const Piece& piece) {return piece.validCaptures();}, blackPieces);
}

Bitboard Board::getWhiteMoveMap(const Piece& p, Pos* to, bool includePiecesAttacks) const
{
	return conditionalGetMap(p, to, includePiecesAttacks, [](const Piece& piece) {return piece.validMoves();}, whitePieces);
}

Bitboard Board::getBlackMoveMap(const Piece& p, Pos* to, bool includePiecesAttacks) const
{
	return conditionalGetMap(p, to, includePiecesAttacks, [](const Piece& piece) {return piece.validMoves();}, blackPieces);
}

template <typename Function>
Bitboard Board::conditionalGetMap(const Piece& p, Pos* to, bool includePiecesAttacks, Function func, std::vector<Piece*>* pieces) const
{
	Bitboard tmp;
	for(long unsigned int i = 0; i < pieces->size(); i++)
		if(pieces->at(i) != &p)
			tmp = tmp | func(*pieces->at(i));
	// we assume that Function type = lambda function, thus calling that lambda function we defined with *pieces->at(i) and returning the corresponding piece.validMoves(); bitboard.
	// Remember, compiler just creates different copies of this function based on the input passed! Validity is entirly based on whats passed... seems a little wacky but its good, and no extra libs needed ;)
	
	if(includePiecesAttacks)
		tmp = tmp | p.validCaptures(to);
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
