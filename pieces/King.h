#ifndef KING_H
#define KING_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class King : public Piece
{
	public:
	King(Pos p, bool white);
	~King();
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>* p, Piece* gameBoard) override;
	
};


#endif
