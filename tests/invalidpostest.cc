#include "../src/Board.h"
#include "../src/defs.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
	{
		game->movePiece(Pos(i, 6), Pos(0, 0));
		game->movePiece(Pos(i, 7), Pos(0, 0));
		
		std::cout << game->toFENString() << std::endl;
	}
	
	for(int i = 0; i < MAX_ROW_COL; i++)
	{
		game->movePiece(Pos(i, 0), Pos(0, 0));
		game->movePiece(Pos(i, 1), Pos(0, 0));
		
		std::cout << game->toFENString() << std::endl;
	}
	

	std::string fs = game->toFENString();
	std::cout << fs << std::endl;
	
	std::cout << "\nchecking...\n" << std::endl;

	std::string test = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	
	delete game;
	if(fs != test)
	{
		std::cout << fs << std::endl << test << std::endl << "FAIL";
		return 1;
	}	
	
	std::cout << "PASS\n";
	return 0;
}
