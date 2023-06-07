#ifndef PLUSMOVE_H
#define PLUSMOVE_H

#include "../MoveBehaviour.h"

class PlusMove : public MoveBehaviour
{
	public:
	PlusMove(Piece* from = nullptr);
	~PlusMove();

	virtual Bitboard validMoves(Pos* p = nullptr) const override;
	virtual void validMoves(std::vector<Pos>& out) override; 
	
	private:
	bool checkPosition(int, int, std::vector<Pos>&);
	bool checkPosition(int, int, Bitboard&) const;
};

#endif
