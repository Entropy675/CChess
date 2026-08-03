#ifndef PLUSMOVE_H
#define PLUSMOVE_H

#include "../MoveBehaviour.h"

class PlusMove : public MoveBehaviour
{
	public:
	PlusMove(Piece* from = nullptr);
	~PlusMove();

	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	virtual Bitboard validCaptures(Pos* p = nullptr) const override;
	Bitboard generate(Pos* p, bool attackMap) const;
	
	private:
	bool checkPosition(int, int, Bitboard&, bool attackMap = false) const;
};

#endif
