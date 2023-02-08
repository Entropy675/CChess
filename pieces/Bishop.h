#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"
#include "../Pos.h"
#include "../defs.h"
#include <vector>

class Bishop : public Piece
{
	public:
	Bishop(Pos p, bool white);
	~Bishop();
	bool isValidMove(Pos p) override;
	void validMoves(std::vector<Pos>* p, Piece* (&gameBoard)[MAX_ROW_COL][MAX_ROW_COL]) override;
	
};




#endif
