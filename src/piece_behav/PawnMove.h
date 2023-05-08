#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "../MoveBehaviour.h"

class PawnMove : public MoveBehaviour
{
	public:
	PawnMove();
	~PawnMove();

	bool enPassantCheckAct(const Pos, const Piece&); // call this before allowing move.
	const Piece& getEnPassantTarget() const;
	
	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	virtual bool isValidMove(const Pos& to, Piece* from) override;

	private:
	void enPassantTarget(Piece*, int);
	int turnToEP;
	Piece* capturableViaEP;
};

#endif
