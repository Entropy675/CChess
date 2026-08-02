#ifndef KNIGHTMOVE_H
#define KNIGHTMOVE_H

#include "../MoveBehaviour.h"

class KnightMove : public MoveBehaviour
{
	public:
	KnightMove(Piece* from = nullptr);
	~KnightMove();

	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	virtual void validMoves(std::vector<Pos>& out) override; 
	
	private:
	void checkPosition(int, int, std::vector<Pos>&);
	void checkPosition(int, int, Bitboard&) const;
};

#endif
