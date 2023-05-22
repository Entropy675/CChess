#ifndef CROSSMOVE_H
#define CROSSMOVE_H

#include "../MoveBehaviour.h"

class CrossMove : public MoveBehaviour
{
	public:
	CrossMove();
	~CrossMove();
	
	virtual Bitboard validMoves(Piece* from) override;
	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	
	private:
	bool checkPosition(int, int, std::vector<Pos>&, Piece*);
	bool checkPosition(int, int, Bitboard&, Piece*);
};

#endif
