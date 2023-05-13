#ifndef KNIGHTMOVE_H
#define KNIGHTMOVE_H

#include "../MoveBehaviour.h"

class KnightMove : public MoveBehaviour
{
	public:
	KnightMove();
	~KnightMove();

	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	virtual bool isValidMove(const Pos& to, Piece* from) override;
	
	private:
	void checkPosition(int, int, std::vector<Pos>&, Piece*, Board*);
};

#endif
