#ifndef KINGMOVE_H
#define KINGMOVE_H

#include "../MoveBehaviour.h"

class KingMove : public MoveBehaviour
{
	public:
	KingMove();
	~KingMove();

	virtual Bitboard validMoves(Piece* from) override;
	virtual void validMoves(std::vector<Pos>& out, Piece* from) override; 
	virtual bool isValidMove(const Pos& to, Piece* from) override;
	
	private:
	void checkPosition(int x, int y, std::vector<Pos>&, Bitboard&, Piece*);
	void checkPosition(int x, int y, Bitboard&, Bitboard&, Piece*);
};

#endif
