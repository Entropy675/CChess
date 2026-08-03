#ifndef CROSSMOVE_H
#define CROSSMOVE_H

#include "../MoveBehaviour.h"

class CrossMove : public MoveBehaviour
{
	public:
	CrossMove(Piece* from = nullptr);
	~CrossMove();
	
	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	virtual Bitboard validCaptures(Pos* p = nullptr) const override;
	Bitboard generate(Pos* p, bool attackMap) const;
	
	private:
	bool checkPosition(int, int, Bitboard&, bool attackMap = false) const;
};

#endif
