#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(1, 7), Pos(2, 5));
	game->movePiece(Pos(6, 0), Pos(5, 2));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(2, 5), Pos(4, 5)); // fail
	game->movePiece(Pos(2, 5), Pos(4, 6)); // fail 
	game->movePiece(Pos(2, 5), Pos(4, 3)); // fail
	game->movePiece(Pos(2, 5), Pos(4, 4)); 
	game->movePiece(Pos(5, 2), Pos(4, 3)); // fail 
	game->movePiece(Pos(5, 2), Pos(4, 4));

	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(6, 7), Pos(5, 5));
	game->movePiece(Pos(4, 4), Pos(5, 2)); 
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(5, 5), Pos(4, 7)); // fail
	game->movePiece(Pos(5, 5), Pos(6, 7)); 
	game->movePiece(Pos(5, 2), Pos(6, 0)); 
	
	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;

	std::string test = "rnbqkb1r/pppppppp/5n2/8/8/8/PPPPPPPP/R1BQKBNR b KQkq - 3 4";
	
	delete game;
	if(fs != test)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
