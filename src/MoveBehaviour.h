#ifndef MOVEBEHAVIOUR_H
#define MOVEBEHAVIOUR_H

#include "defs.h"
#include "Pos.h"
#include "Piece.h"
#include "Bitboard.h"
#include <vector>

/* MoveBehaviour
** Pure virtual class, children are primitive and modular behaviours.
** These behaviours can be added to Pieces (in their movebehavArr),
** where they are used to compute the valid moves of that piece.
** Ex: Queen has the combination of the X (Cross) and + (Plus) behaviours,
** and can go in either of those directions.
*/
class MoveBehaviour
{
public:
	MoveBehaviour(Piece* from = nullptr);
	virtual ~MoveBehaviour();
	
	Piece* setFrom(Piece*);

	virtual Bitboard validCaptures(Pos* p = nullptr) const;
	virtual bool isValidMove(const Pos& to);
	
	virtual Bitboard validMoves(Pos* p = nullptr) const = 0;
	virtual void validMoves(std::vector<Pos>& out) = 0; // ptr cant be const ref because of pawn EP set & kill

protected:
	Piece* from;
};


#endif
