#include "../src/Board.h"
#include <iostream>

// Regression test: a move REJECTED while a piece is pinned must not corrupt
// that piece so it can never make the move again once unpinned.
//
// Root cause guarded: Piece::move commits pos = destination before movePiece
// runs the king-safety check. When the king check rejects the move, movePiece
// must roll pos back to the origin, else the piece's pos desyncs from the board
// and validMoves() is generated from a phantom square forever after.
//
// Occupies the same 'loader' slot as ChessGameLinux: drives a Board and reports
// pass/fail via the exit code (0 pass, 1 fail) so the glob runner catches it.
// getCharacter() returns the piece TYPE in uppercase regardless of colour.

static bool at(Board* g, int x, int y, char typeUpper)
{
	Piece* p = (*g)[x][y];
	return p != nullptr && p->getCharacter() == typeUpper;
}

int main()
{
	int fail = 0;

	// --- Case 1: bishop pinned along the e-file by a queen (pin from a check block), real game moves ---
	{
		Board* g = new Board(); g->setStartingBoard(true);
		int seq[][4] = {
			{3,6,3,4},{4,1,4,3},{3,7,3,5},{4,3,3,4},{3,5,4,4},{5,0,4,1},{2,6,2,5}
		}; // d4 e5 Qd3 exd4 Qe4+ Be7(block) c3
		for(auto& m : seq) g->movePiece(Pos(m[0],m[1]), Pos(m[2],m[3]));

		if(g->movePiece(Pos(4,1), Pos(5,2)) != ChessStatus::FAIL)   // Be7-f6 while pinned: must fail
			{ std::cout << "case1: pinned Be7-f6 wrongly allowed\n"; fail++; }
		g->movePiece(Pos(0,1), Pos(0,3));                           // ...a5 (waiting)
		g->movePiece(Pos(4,4), Pos(5,4));                           // Qf4 (leaves e-file -> unpins)
		ChessStatus r = g->movePiece(Pos(4,1), Pos(5,2));           // Be7-f6: now legal
		std::cout << "case1 fen: " << g->toFENString() << "\n";
		if(r != ChessStatus::SUCCESS || !at(g,5,2,'B') || (*g)[4][1] != nullptr)
			{ std::cout << "case1: unpinned Be7-f6 rejected (pos-corruption regression)\n"; fail++; }
		delete g;
	}

	// --- Case 2: knight pinned along a diagonal by a bishop (guaranteed absolute pin) ---
	{
		Board* g = new Board(); g->setEmptyBoard(true); // white to move
		g->placePiece(6,7,'K',true);   // white Kg1  (off the bishop's lines)
		g->placePiece(0,4,'B',true);   // white Ba4  (pins along a4-b5-c6-d7-e8)
		g->placePiece(4,0,'K',false);  // black Ke8
		g->placePiece(2,2,'N',false);  // black Nc6  (pinned; d7 empty)
		g->placePiece(0,1,'P',false);  // black a7 pawn (for a waiting move)

		g->movePiece(Pos(6,7), Pos(6,6)); // Kg1-g2 (white waiting) -> black to move
		if(g->movePiece(Pos(2,2), Pos(3,4)) != ChessStatus::FAIL)   // Nc6-d4 while pinned: must fail
			{ std::cout << "case2: pinned Nc6-d4 wrongly allowed\n"; fail++; }
		g->movePiece(Pos(0,1), Pos(0,2));                           // ...a6 (waiting)
		g->movePiece(Pos(0,4), Pos(3,7));                           // Ba4-d1 (leaves diagonal -> unpins)
		ChessStatus r = g->movePiece(Pos(2,2), Pos(3,4));           // Nc6-d4: now legal
		std::cout << "case2 fen: " << g->toFENString() << "\n";
		if(r != ChessStatus::SUCCESS || !at(g,3,4,'N') || (*g)[2][2] != nullptr)
			{ std::cout << "case2: unpinned Nc6-d4 rejected (pos-corruption regression)\n"; fail++; }
		delete g;
	}

	std::cout << (fail == 0 ? "pinreleasetest: PASS\n" : "pinreleasetest: FAIL\n");
	return fail == 0 ? 0 : 1;
}
