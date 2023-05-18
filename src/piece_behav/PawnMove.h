#ifndef PAWNMOVE_H
#define PAWNMOVE_H

#include "../MoveBehaviour.h"

class PawnMove : public MoveBehaviour
{
	public:
	PawnMove();
	~PawnMove();

	void EPValidateTarget(Piece*, bool);
	bool enPassantCheckAct(const Pos, const Piece&); // call this before allowing move.
	const Piece* getEnPassantTarget() const;
	Bitboard validPawnCaptures(Piece* from); // only piece that has different captures from moves, need this for threat bitboard
	
	virtual Bitboard validMoves(Piece* from) override;
	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	virtual bool isValidMove(const Pos& to, Piece* from) override;

	private:
	void EPSetTarget(Piece*, int);
	
	int turnToEP;
	Piece* capturableViaEP;
};

#endif
