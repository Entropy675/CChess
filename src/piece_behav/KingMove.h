#ifndef KINGMOVE_H
#define KINGMOVE_H

#include "../MoveBehaviour.h"

class KingMove : public MoveBehaviour
{
	public:
	KingMove();
	~KingMove();

	virtual Bitboard validCaptures(Piece* from) override;
	
	virtual Bitboard validMoves(Piece* from) override;
	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	
	private:
	void checkPosition(int x, int y, std::vector<Pos>&, Piece*);
	void checkPosition(int x, int y, Bitboard&, Piece*, bool = true);
};

#endif
