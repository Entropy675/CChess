#ifndef CROSSMOVE_H
#define CROSSMOVE_H

#include "../MoveBehaviour.h"

class CrossMove : public MoveBehaviour
{
	public:
	CrossMove(Piece* from = nullptr);
	~CrossMove();
	
	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	
	private:
	bool checkPosition(int, int, Bitboard&) const;
};

#endif
