#ifndef KINGMOVE_H
#define KINGMOVE_H

#include "../MoveBehaviour.h"

class KingMove : public MoveBehaviour
{
	public:
	KingMove();
	~KingMove();

	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	virtual bool isValidMove(const Pos& to, Piece* from) override;
};

#endif
