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
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>& p) override;
	
	bool move(Pos) override;
	void enPassantTarget(Piece*);
	
	private:
	bool canEP;
	Piece* capturableViaEP;
};




#endif
