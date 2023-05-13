#include "KnightMove.h"

KnightMove::KnightMove() {}
KnightMove::~KnightMove() {}

// returns true meaning cPos was added to out.
void KnightMove::checkPosition(int x, int y, std::vector<Pos>& out, Piece* from, Board* game)
{
	Piece* temp = game->getPiece(Pos(x,y));
	if(temp == nullptr)
		out.push_back(Pos(x,y));
	else if(temp->isWhite() != from->isWhite())
		out.push_back(Pos(x,y));
}

void KnightMove::validMoves(std::vector<Pos>& out, Piece* from)
{
	Log log(2);
	Pos origin = from->getPos();
	Board* game = from->getBoard();
	
	std::vector<Pos> temp;
	
	if(Pos::isValid(origin.getX() + 2, origin.getY()))
	{
		Pos cTemp(origin.getX() + 2, origin.getY());
		
		checkPosition(cTemp.getX(), cTemp.getY() + 1, out, from, game);
		checkPosition(cTemp.getX(), cTemp.getY() - 1, out, from, game);
	}
	
	if(Pos::isValid(origin.getX() - 2, origin.getY()))
	{
		Pos cTemp(origin.getX() - 2, origin.getY());
		
		checkPosition(cTemp.getX(), cTemp.getY() + 1, out, from, game);
		checkPosition(cTemp.getX(), cTemp.getY() - 1, out, from, game);
	}
	
	if(Pos::isValid(origin.getX(), origin.getY() + 2))
	{
		Pos cTemp(origin.getX(), origin.getY() + 2);
		
		checkPosition(cTemp.getX() + 1, cTemp.getY(), out, from, game);
		checkPosition(cTemp.getX() - 1, cTemp.getY(), out, from, game);
	}
	
	if(Pos::isValid(origin.getX(), origin.getY() - 2))
	{
		Pos cTemp(origin.getX(), origin.getY() - 2);
		
		checkPosition(cTemp.getX() + 1, cTemp.getY(), out, from, game);
		checkPosition(cTemp.getX() - 1, cTemp.getY(), out, from, game);
	}
	
	// logging, all possible moves are logged at level 2
	log.append("KNIGHT MOVES: VArr " + std::to_string(out.size()) + ":");
	for (auto &x : out)
		log.append(x.toString() + ", ");
	log.setLogLevel(1);
	log.append(" trn: " + std::to_string(game->getTurnFEN()) + "total moves: " + std::to_string(game->getMoves()) + "\n");
}

bool KnightMove::isValidMove(const Pos& to, Piece* from)
{
	std::vector<Pos> templist;
	validMoves(templist, from);
	for(long unsigned int i = 0; i < templist.size(); i++)
		if(templist[i] == to)
			return true;
	return false;
}