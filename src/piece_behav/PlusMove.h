#ifndef PLUSMOVE_H
#define PLUSMOVE_H

#include "../MoveBehaviour.h"

class PlusMove : public MoveBehaviour
{
	public:
	PlusMove();
	~PlusMove();

	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	virtual bool isValidMove(const Pos& to, Piece* from) override;
};

#endif
