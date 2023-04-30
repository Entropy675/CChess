#ifndef CROSSMOVE_H
#define CROSSMOVE_H

#include "../MoveBehaviour.h"

class CrossMove : public MoveBehaviour
{
	public:
	CrossMove();
	~CrossMove();

	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	virtual bool isValidMove(const Pos& to, Piece* from) override;
};

#endif
