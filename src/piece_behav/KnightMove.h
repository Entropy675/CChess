#ifndef KNIGHTMOVE_H
#define KNIGHTMOVE_H

#include "../MoveBehaviour.h"

class KnightMove : public MoveBehaviour
{
	public:
	KnightMove(Piece* from = nullptr);
	~KnightMove();

	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	virtual Bitboard validCaptures(Pos* p = nullptr) const override;
	Bitboard generate(Pos* p, bool attackMap) const;
	
	private:
	void checkPosition(int, int, Bitboard&, bool attackMap = false) const;
};

#endif
