#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "../MoveBehaviour.h"

class PawnMove : public MoveBehaviour
{
	public:
	PawnMove(Piece* from = nullptr);
	~PawnMove();

	void EPValidateTarget(Piece*, bool);
	bool enPassantCheckAct(const Pos, const Piece&); // call this before allowing move.
	const Piece* getEnPassantTarget() const;	
	
	virtual Bitboard validCaptures(Pos* p = nullptr) const override;
	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	
	virtual void validMoves(std::vector<Pos>& out) override; 

	private:
	void EPSetTarget(Piece*, int);
	
	int turnToEP;
	Piece* capturableViaEP;
};

#endif
