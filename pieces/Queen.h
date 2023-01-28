#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Queen : public Piece
{
	public:
	Queen(Pos p, bool white);
	~Queen();
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>* p, Piece* gameBoard) override;
	
};




#endif
