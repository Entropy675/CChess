#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Knight : public Piece
{
	public:
	Knight(Pos p, bool white);
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>* p, Piece* gameBoard) override;
	void move(Pos p) override;
	
};



#endif
