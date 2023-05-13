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
	bool checkPosition(Pos&, Pos&, std::vector<Pos>&, Piece*, Board*);
	bool checkPositionIntermediate(Pos&, Pos&, std::vector<Pos>&, Piece*, Board*);
};

#endif
