#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	
	game->movePiece(Pos(3, 6), Pos(3, 4));
	game->movePiece(Pos(4, 1), Pos(4, 3));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(3, 4), Pos(4, 3));
	game->movePiece(Pos(5, 1), Pos(5, 3)); // now enpassant should be true
	
	std::cout << game->toFENString() << std::endl;
	
	bool exitFailFlag = !game->isEnpassantOnBoard();
	if(!game->isEnpassantOnBoard())
		std::cout << "The games EnpassantOnBoard flag is invalid." << std::endl;
	
	game->movePiece(Pos(4, 3), Pos(5, 2));

	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;

	std::string test = "rnbqkbnr/pppp2pp/5P2/8/8/8/PPP1PPPP/RNBQKBNR b KQkq - 0 3";
	
	delete game;
	if(fs != test || exitFailFlag)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		if(exitFailFlag)
			std::cout << "Either also or caused by game flag for enpassant not being active when it should be." << std::endl;
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
