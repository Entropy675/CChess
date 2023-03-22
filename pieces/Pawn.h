#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"

#include <vector>


class Pawn : public Piece
{
	public:
	Pawn(Pos p, bool white, Board* g);
	~Pawn();
	
	virtual bool isValidMove(const Pos p) override;
	virtual void validMoves(std::vector<Pos>& p) override;
	virtual bool move(const Pos) override;
	
	private:
	void enPassantTarget(Piece*, int);
	int turnToEP;
	Piece* capturableViaEP;
};




#endif
