#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "../defs.h"
#include "../MoveBehaviour.h"

class PawnMove : public MoveBehaviour
{
	public:
	PawnMove();
	~PawnMove();

	bool enPassantCheckAct(const Pos, const Piece&); // call this before allowing move. 
	virtual void validMoves(std::vector<Pos>& out, const Piece* from) override;
	virtual bool isValidMove(const Pos& to, const Piece& from) override;

	private:
	void enPassantTarget(Piece*, int);
	int turnToEP;
	Piece* capturableViaEP;
};

#endif
