#ifndef KING_H
#define KING_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"

#include <vector>

class King : public Piece
{
	public:
	King(Pos p, bool white, Board* g);
	~King();
	
	virtual bool isValidMove(const Pos p) override;
	virtual void validMoves(std::vector<Pos>& p) override;
	virtual bool move(const Pos) override;
};


#endif
