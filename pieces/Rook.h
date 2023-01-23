#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Rook : public Piece
{
	public:
	Rook(Pos p, bool white);
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>* p, Piece* gameBoard) override;
	void move(Pos p) override;
	
};




#endif
