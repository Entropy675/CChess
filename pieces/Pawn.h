#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Pawn : public Piece
{
	public:
	Pawn(Pos p, bool white);
	~Pawn();
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>* p, Piece* gameBoard) override;
	
};




#endif
