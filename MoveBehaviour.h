#ifndef MOVEBEHAVIOUR_H
#define MOVEBEHAVIOUR_H

#include "Piece.h"
#include "Vector.h"

/* MoveBehaviour
** Class contains primitive and modular behaviours.
** These behaviours can be added to Pieces, which modifies
** their movement pattarns.
** Ex: Queen has the combination of the X and + behaviours.
*/
class MoveBehaviour
{
public:
  MoveBehaviour(Piece* = nullptr);
  ~MoveBehaviour();

  virtual void validMoves(std::vector<Pos>&) = 0;
	virtual bool isValidMove(const Pos&) = 0;

private:
  Piece* p;
}


#endif
