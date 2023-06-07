#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	
	game->movePiece(Pos(3,6), Pos(3,4));
	game->movePiece(Pos(4,1), Pos(4,3));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(4,7), Pos(3,6));
	game->movePiece(Pos(3,0), Pos(6,3));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(7,6), Pos(7,4)); // fail
	game->movePiece(Pos(4,6), Pos(4,5));
	game->movePiece(Pos(4,3), Pos(3,4));
	
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(3,6), Pos(3,5));
	game->movePiece(Pos(6,3), Pos(5,3));

	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(6,6), Pos(6,4)); // fail
	game->movePiece(Pos(4,5), Pos(4,4));
	game->movePiece(Pos(5,3), Pos(5,5));

	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(3,5), Pos(3,4));
	game->movePiece(Pos(6,1), Pos(6,2));
	
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(6,7), Pos(7,5));
	game->movePiece(Pos(5,5), Pos(5,6));
	
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(4,4), Pos(4,3)); // fail
	game->movePiece(Pos(7,5), Pos(5,6));
	game->movePiece(Pos(4,0), Pos(4,1));
		
	std::cout << game->toFENString() << std::endl;
		
	game->movePiece(Pos(2,7), Pos(6,3));
	game->movePiece(Pos(7,1), Pos(7,2)); // fail
	game->movePiece(Pos(7,1), Pos(7,3)); // fail
	game->movePiece(Pos(7,1), Pos(7,2)); // fail
	game->movePiece(Pos(5,1), Pos(5,2));
	
	
	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;

	std::string test = "rnb2bnr/ppppk2p/5pp1/6B1/3KP3/8/PPP2NPP/RN1Q1B1R w KQkq - 0 10";
	
	delete game;
	if(fs != test)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
