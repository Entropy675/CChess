#include "../src/Board.h"
#include <iostream>

int main() 
{
	Board* game = new Board();
	game->setStartingBoard(true);
	game->movePiece(Pos(0, 6), Pos(0, 4));
	game->movePiece(Pos(0, 1), Pos(0, 3));
	game->movePiece(Pos(1, 6), Pos(1, 4));
	game->movePiece(Pos(1, 1), Pos(1, 3));
	game->movePiece(Pos(2, 6), Pos(2, 4));
	game->movePiece(Pos(2, 1), Pos(2, 3));
	game->movePiece(Pos(3, 6), Pos(3, 4));
	game->movePiece(Pos(3, 1), Pos(3, 3));
	game->movePiece(Pos(4, 6), Pos(4, 4));
	game->movePiece(Pos(4, 1), Pos(4, 3));
	game->movePiece(Pos(5, 6), Pos(5, 4));
	game->movePiece(Pos(5, 1), Pos(5, 3));
	game->movePiece(Pos(6, 6), Pos(6, 4));
	game->movePiece(Pos(6, 1), Pos(6, 3));
	game->movePiece(Pos(7, 6), Pos(7, 4));
	game->movePiece(Pos(7, 1), Pos(7, 3));
	
	std::cout << "this ran" << std::endl;
	
	std::string fs = game->toFENString();
	if(fs != "rnbqkbn/8/8r/pppppppp/PPPPPPPP/8/8/RNBQKBNR w KQkq - 0 8")
	{
		std::cout << fs << std::endl << "FAIL" << std::endl;
		return 1;
	}	
	return 0;
}
