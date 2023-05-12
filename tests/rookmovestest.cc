#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	
	game->movePiece(Pos(0, 6), Pos(0, 5));
	game->movePiece(Pos(0, 1), Pos(0, 3));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(0, 7), Pos(0, 6));
	game->movePiece(Pos(0, 0), Pos(0, 3)); // fail
	game->movePiece(Pos(0, 0), Pos(0, 4)); // fail
	game->movePiece(Pos(0, 0), Pos(0, 2));
	
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(1, 6), Pos(1, 4));
	game->movePiece(Pos(0, 2), Pos(7, 2)); 
	
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(0, 6), Pos(1, 6));
	game->movePiece(Pos(7, 2), Pos(7, 6));

	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(7, 7), Pos(7, 6));
	game->movePiece(Pos(7, 1), Pos(7, 3)); 

	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(1, 6), Pos(1, 3)); // fail 
	game->movePiece(Pos(1, 6), Pos(1, 4)); // fail 
	game->movePiece(Pos(1, 6), Pos(1, 5)); 
	
	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;

	std::string test = "1nbqkbnr/1pppppp1/8/p6p/1P6/PR6/2PPPPPR/1NBQKBN1 b KQkq - 1 6";
	
	delete game;
	if(fs != test)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
