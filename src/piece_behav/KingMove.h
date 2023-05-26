#ifndef KINGMOVE_H
#define KINGMOVE_H

#include "../MoveBehaviour.h"

class KingMove : public MoveBehaviour
{
	public:
	KingMove(Piece* from = nullptr);
	~KingMove();

	virtual Bitboard validCaptures() override;
	virtual Bitboard validMoves() override;
	virtual void validMoves(std::vector<Pos>& out) override; 
	
	private:
	void checkPosition(int x, int y, std::vector<Pos>&);
	void checkPosition(int x, int y, Bitboard&, bool = true);
};

#endif
