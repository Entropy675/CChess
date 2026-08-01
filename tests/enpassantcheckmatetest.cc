#include "../src/Board.h"
#include <iostream>

// Free helpers over the public custom-board API (Board owns the privileged state).
static void   setup(Board& g, bool whiteToMove)                 { g.setEmptyBoard(whiteToMove); }
static Piece* place(Board& g, int x, int y, char type, bool w)  { return g.placePiece(x, y, type, w); }

int main()
{
	// "Would-be checkmate, except en passant is the only escape."
	// White: Kh4 Ph5 ; Black: Kg8 Ph6 Rg3 Ne4 and Pg7 about to double-push.
	Board* game = new Board();
	setup(*game, false);                 // black to move (plays the double-push)
	place(*game, 7, 4, 'K', true);       // white Kh4
	place(*game, 7, 3, 'P', true);       // white Ph5
	place(*game, 6, 0, 'K', false);      // black Kg8
	place(*game, 7, 2, 'P', false);      // black Ph6
	place(*game, 6, 5, 'R', false);      // black Rg3
	place(*game, 4, 4, 'N', false);      // black Ne4
	place(*game, 6, 1, 'P', false);      // black Pg7

	game->movePiece(Pos(6, 1), Pos(6, 3)); // g7-g5+  (arms en passant on h5)
	std::string afterCheck = game->toFENString();
	std::cout << afterCheck << std::endl;

	bool inCheck = game->sideToMoveInCheck();
	bool hasEP   = game->sideToMoveHasLegalEnPassant();
	bool mate    = game->isCheckmate();
	std::cout << "inCheck=" << inCheck << " hasLegalEP=" << hasEP << " isCheckmate=" << mate << std::endl;

	game->movePiece(Pos(6, 1), Pos(6, 4)); // fail: pawn already moved
	game->movePiece(Pos(7, 4), Pos(6, 4)); // fail: Kg4 attacked by Rg3
	game->movePiece(Pos(7, 4), Pos(6, 3)); // fail: Kxg5 (defended)
	game->movePiece(Pos(7, 3), Pos(6, 2)); // h5xg6 e.p. -- the ONLY legal move
	std::string afterEP = game->toFENString();
	std::cout << afterEP << std::endl;

	std::cout << "\nchecking...\n" << std::endl;
	std::string expectCheck = "6k1/8/7p/6pP/4n2K/6r1/8/8 w ---- g5 0 2";
	std::string expectEP    = "6k1/8/6Pp/8/4n2K/6r1/8/8 b ---- - 0 2";

	delete game;

	if(!inCheck || !hasEP || mate || afterCheck != expectCheck || afterEP != expectEP)
	{
		std::cout << "inCheck/hasEP/!mate = " << inCheck << hasEP << (!mate) << std::endl;
		std::cout << afterCheck << "\n" << expectCheck << std::endl;
		std::cout << afterEP    << "\n" << expectEP    << std::endl;
		std::cout << "FAIL\n";
		return 1;
	}

	std::cout << "PASS\n";
	return 0;
}
