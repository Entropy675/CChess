#ifndef PLUSMOVE_H
#define PLUSMOVE_H

#include "../MoveBehaviour.h"

class PlusMove : public MoveBehaviour
{
	public:
	PlusMove();
	~PlusMove();

	virtual Bitboard validMoves(Piece* from) override;
	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	
	private:
	bool checkPosition(int, int, std::vector<Pos>&, Piece*);
	bool checkPosition(int, int, Bitboard&, Piece*);
};

#endif
