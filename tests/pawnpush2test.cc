#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	game->movePiece(Pos(0, 6), Pos(0, 4));
	game->movePiece(Pos(0, 1), Pos(0, 3));
	
	game->movePiece(Pos(1, 6), Pos(1, 3)); // illegal
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(1, 6), Pos(1, 4));
	game->movePiece(Pos(1, 1), Pos(1, 3));
	
	game->movePiece(Pos(2, 6), Pos(2, 3)); // illegal
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(2, 6), Pos(2, 4));
	game->movePiece(Pos(2, 1), Pos(2, 3));
	
	game->movePiece(Pos(3, 6), Pos(3, 3)); // illegal
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(3, 6), Pos(3, 4));
	game->movePiece(Pos(3, 1), Pos(3, 3));
	
	game->movePiece(Pos(4, 6), Pos(4, 3)); // illegal
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(4, 6), Pos(4, 4));
	game->movePiece(Pos(4, 1), Pos(4, 3));
	
	game->movePiece(Pos(5, 6), Pos(5, 3)); // illegal
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(5, 6), Pos(5, 4));
	game->movePiece(Pos(5, 1), Pos(5, 3));
	
	game->movePiece(Pos(6, 6), Pos(6, 3)); // illegal
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(6, 6), Pos(6, 4));
	game->movePiece(Pos(6, 1), Pos(6, 3));
	
	game->movePiece(Pos(7, 6), Pos(7, 3)); // illegal
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(7, 6), Pos(7, 4));
	game->movePiece(Pos(7, 1), Pos(7, 3));
	
	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;
	
	std::string test = "rnbqkbnr/8/8/pppppppp/PPPPPPPP/8/8/RNBQKBNR w KQkq - 0 9";
	
	delete game;
	if(fs != test)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
