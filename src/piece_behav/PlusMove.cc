#include "PlusMove.h"

PlusMove::PlusMove() {}
PlusMove::~PlusMove() {}

// returns false meaning continue searching - have yet to hit a piece or invalid square.
bool PlusMove::checkPosition(int x, int y, std::vector<Pos>& out, Piece* from, Board* game)
{
	if(Pos::isValid(x, y))
	{
		Piece* temp = game->getPiece(Pos(x,y));
		if(temp == nullptr)
			out.push_back(Pos(x,y));
		else
		{
			if(temp->isWhite() != from->isWhite())
				out.push_back(Pos(x,y));
			return true;
		}
		return false;
	}
	return true;
}

void PlusMove::validMoves(std::vector<Pos>& out, Piece* from)
{
	Log log(2);
	Pos origin = from->getPos();
	Board* game = from->getBoard();
	bool stopR = false;
	bool stopL = false;
	bool stopU = false;
	bool stopD = false;
	
	for(int i = 1; i < 8; i++)
	{
		if(!stopR)
			stopR = checkPosition(origin.getX() + i, origin.getY(), out, from, game);
		
		if(!stopL)
			stopL = checkPosition(origin.getX() - i, origin.getY(), out, from, game);
		
		if(!stopD)
			stopD = checkPosition(origin.getX(), origin.getY() + i, out, from, game);
		
		if(!stopU)
			stopU = checkPosition(origin.getX(), origin.getY() - i, out, from, game);
		
		if(stopU && stopD && stopR && stopL)
			break;
	}
	
	// logging, all possible moves are logged at level 2
	log.append("PLUS VALID MOVE: VArr " + std::to_string(out.size()) + ":");
	for (auto &x : out)
		log.append(x.toString() + ", ");
	log.setLogLevel(1);
	log.append(" trn: " + std::to_string(game->getTurnFEN()) + "total moves: " + std::to_string(game->getMoves()) + "\n");
}
bool PlusMove::isValidMove(const Pos& to, Piece* from)
{
	std::vector<Pos> templist;
	validMoves(templist, from);
	for(long unsigned int i = 0; i < templist.size(); i++)
		if(templist[i] == to)
			return true;
	return false;
}