#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"

#include <vector>

class Knight : public Piece
{
	public:
	Knight(Pos p, bool white, Board* g);
	~Knight();

	virtual bool isValidMove(const Pos p) override;
	virtual void validMoves(std::vector<Pos>& p) override;
	virtual bool move(const Pos) override;
};



#endif
