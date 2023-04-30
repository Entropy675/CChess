#ifndef MOVEBEHAVIOUR_H
#define MOVEBEHAVIOUR_H

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

  virtual void validMoves(std::vector<Pos>& out, const Piece& from) = 0;
	virtual bool isValidMove(const Pos& to, const Piece& from) = 0;
};


#endif
