#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Knight : public Piece
{
	public:
	Knight(Pos p, bool white);
	~Knight();
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>* p, Piece* (&gameBoard)[MAX_ROW_COL][MAX_ROW_COL]) override;
	
};



#endif
