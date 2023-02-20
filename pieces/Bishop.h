#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Bishop : public Piece
{
	public:
	Bishop(Pos p, bool white, Board* g);
	~Bishop();
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>& p) override;
	
};




#endif
