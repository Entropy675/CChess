#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	game->movePiece(Pos(3, 6), Pos(3, 4));
	game->movePiece(Pos(0, 1), Pos(0, 3));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(3, 4), Pos(3, 3));
	game->movePiece(Pos(0, 3), Pos(0, 4));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(3, 3), Pos(3, 2));
	game->movePiece(Pos(0, 4), Pos(0, 5));
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(3, 2), Pos(4, 1));
	game->movePiece(Pos(0, 5), Pos(1, 6));
	
	std::cout << game->toFENString() << std::endl;
	
	std::string input = "Q";
	
	game->movePiece(Pos(4, 1), Pos(3, 0));
	bool valid = game->registerPromotion(input);
	
	std::cout << game->toFENString() << std::endl;
	
	game->movePiece(Pos(1, 6), Pos(0, 7));
	input = "K";
	game->registerPromotion(input); // illegal
	input = "N";
	valid = valid && game->registerPromotion(input);
	
	std::cout << game->toFENString() << std::endl;
	
	if(!valid)
	{
		std::cout << "The promotion registration was invalid." << std::endl;
		return 2;
	}
	else
	{
		std::cout << "~Valid promotion registration~" << std::endl;
	}
	
	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;
	
	std::cout << "!!!\nWarning! This test case does not properly consider castling! When castling is implemented, this will fail incorrectly.\n!!!" << std::endl;
	
	std::string test = "rnbQkbnr/1ppp1ppp/8/8/8/8/P1P1PPPP/nNBQKBNR w KQkq - 0 6";
	if(fs != test)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
