#ifndef MOVEBEHAVIOUR_H
#define MOVEBEHAVIOUR_H

#include "defs.h"
#include "Pos.h"
#include "Piece.h"
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

	virtual void validMoves(std::vector<Pos>& out, Piece* from) = 0; // ptr cant be const ref because of pawn EP set & kill
	virtual bool isValidMove(const Pos& to, Piece* from) = 0;
};


#endif
