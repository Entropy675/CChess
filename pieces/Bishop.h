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
	
	virtual bool isValidMove(const Pos p) override;
	virtual void validMoves(std::vector<Pos>& p) override;
	virtual bool move(const Pos) override;
};




#endif
