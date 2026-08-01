#include "../src/Board.h"
#include <iostream>

int main()
{
	// Fool's mate: 1. f3 e5  2. g4 Qh4#  -- fastest checkmate in chess.
	Board* game = new Board();
	game->setStartingBoard(true);

	game->movePiece(Pos(5, 6), Pos(5, 5)); // f3  (f2-f3)
	game->movePiece(Pos(4, 1), Pos(4, 3)); // e5  (e7-e5)
	std::cout << game->toFENString() << std::endl;

	// not mate yet
	bool midMate = game->isCheckmate();

	game->movePiece(Pos(6, 6), Pos(6, 4)); // g4  (g2-g4)
	game->movePiece(Pos(3, 0), Pos(7, 4)); // Qh4# (Qd8-h4)
	std::string fs = game->toFENString();
	std::cout << fs << std::endl;

	bool inCheck = game->sideToMoveInCheck();
	bool mate    = game->isCheckmate();
	std::cout << "midMate=" << midMate << " inCheck=" << inCheck << " isCheckmate=" << mate << std::endl;

	std::cout << "\nchecking...\n" << std::endl;
	std::string test = "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR w KQkq - 1 3";

	bool logic = !midMate && inCheck && mate; // white checkmated after Qh4#

	delete game;

	if(!logic || fs != test)
	{
		std::cout << "midMate=" << midMate << " inCheck=" << inCheck << " mate=" << mate << std::endl;
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}

	std::cout << "PASS\n";
	return 0;
}
