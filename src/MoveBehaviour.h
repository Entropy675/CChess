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
	MoveBehaviour();
	virtual ~MoveBehaviour();

	virtual Bitboard validCaptures(Piece* from);
	virtual bool isValidMove(const Pos& to, Piece* from);
	
	virtual Bitboard validMoves(Piece* from) = 0;
	virtual void validMoves(std::vector<Pos>& out, Piece* from) = 0; // ptr cant be const ref because of pawn EP set & kill
};


#endif
