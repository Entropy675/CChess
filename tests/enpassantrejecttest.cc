#include "../src/Board.h"
#include <iostream>

// Regression: an en-passant capture that is ILLEGAL (leaves own king in check)
// must be rejected AND leave the board unchanged. The EP victim is killed inside
// Piece::move before the king check, so movePiece must restore it on rejection.
// Position: White Ka5,Pb5 ; Black Rh5,Pc7,Kh8. Black c7-c5, then White bxc6 e.p.
// is illegal (removing both 5th-rank pawns exposes Ka5 to Rh5).
int main()
{
	Board* g = new Board();
	g->setEmptyBoard(false); // black to move
	g->placePiece(0,3,'K',true);   // Ka5
	g->placePiece(1,3,'P',true);   // Pb5
	g->placePiece(7,3,'R',false);  // Rh5
	g->placePiece(2,1,'P',false);  // Pc7
	g->placePiece(7,0,'K',false);  // Kh8

	g->movePiece(Pos(2,1), Pos(2,3));            // c7-c5 (sets EP target on c5)
	std::string before = g->toFENString();

	ChessStatus r = g->movePiece(Pos(1,3), Pos(2,2)); // White bxc6 e.p. -- illegal
	bool rejected  = (r == ChessStatus::FAIL);
	bool pawnAlive = ((*g)[2][3] != nullptr);         // black c5 pawn must still be there
	std::string after = g->toFENString();

	std::cout << "before: " << before << "\n";
	std::cout << "after:  " << after  << "\n";

	bool ok = rejected && pawnAlive;
	// board (piece placement) must be identical; only the EP-target flag may differ
	std::string bp = before.substr(0, before.find(' '));
	std::string ap = after.substr(0, after.find(' '));
	ok = ok && (bp == ap);

	std::cout << (ok ? "enpassantrejecttest: PASS\n" : "enpassantrejecttest: FAIL\n");
	delete g;
	return ok ? 0 : 1;
}
