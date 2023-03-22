#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Rook : public Piece
{
	public:
	Rook(Pos p, bool white, Board* g);
	~Rook();
	
	virtual bool isValidMove(const Pos p) override;
	virtual void validMoves(std::vector<Pos>& p) override;
	virtual bool move(const Pos) override;
};




#endif
