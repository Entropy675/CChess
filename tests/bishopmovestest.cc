#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	
	game->movePiece(Pos(3, 6), Pos(3, 4));
	game->movePiece(Pos(4, 1), Pos(4, 3));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(2, 7), Pos(5, 4));
	game->movePiece(Pos(1, 1), Pos(1, 3)); 
	
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(5, 4), Pos(4, 3));
	game->movePiece(Pos(2, 0), Pos(5, 3)); // fail 
	game->movePiece(Pos(2, 0), Pos(0, 2));
	
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(4, 3), Pos(3, 4)); // fail
	game->movePiece(Pos(4, 3), Pos(1, 0)); // fail
	game->movePiece(Pos(4, 3), Pos(2, 1)); 
	game->movePiece(Pos(0, 2), Pos(1, 1)); 

	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(4, 6), Pos(4, 5)); 
	game->movePiece(Pos(1, 1), Pos(3, 3)); 

	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(3, 7), Pos(5, 4)); // fail 
	game->movePiece(Pos(3, 7), Pos(5, 5)); 
	game->movePiece(Pos(3, 3), Pos(5, 5)); 

	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(5, 7), Pos(4, 6)); 
	game->movePiece(Pos(5, 5), Pos(4, 6)); 

	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;

	std::string test = "rn1qkbnr/p1Bp1ppp/8/1p6/3P4/4P3/PPP1bPPP/RN2K1NR w KQkq - 0 8";
	
	delete game;
	if(fs != test)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
