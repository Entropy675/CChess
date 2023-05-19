#ifndef KNIGHTMOVE_H
#define KNIGHTMOVE_H

#include "../MoveBehaviour.h"

class KnightMove : public MoveBehaviour
{
	public:
	KnightMove();
	~KnightMove();

	virtual Bitboard validMoves(Piece* from) override;
	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	
	private:
	void checkPosition(int, int, std::vector<Pos>&, Piece*);
	void checkPosition(int, int, Bitboard&, Piece*);
};

#endif
