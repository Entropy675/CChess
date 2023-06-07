#ifndef KINGMOVE_H
#define KINGMOVE_H

#include "../MoveBehaviour.h"

class KingMove : public MoveBehaviour
{
	public:
	KingMove(Piece* from = nullptr);
	~KingMove();

	virtual Bitboard validCaptures(Pos* p = nullptr) const override;
	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	virtual void validMoves(std::vector<Pos>& out) override; 
	
	private:
	void checkPosition(int x, int y, std::vector<Pos>&);
	void checkPosition(int x, int y, Bitboard&) const;
};

#endif
