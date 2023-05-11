#include "CrossMove.h"

CrossMove::CrossMove() {}
CrossMove::~CrossMove() {}


bool CrossMove::checkPosition(Pos& origin, Pos& cPos, std::vector<Pos>& out, Piece* from, Board* game)
{
	Log log(1);
	
	if(cPos != origin)
	{
		Piece* temp = game->getPiece(cPos);
		if(temp == nullptr)
			out.push_back(cPos);
		else
		{
			if(temp->isWhite() != from->isWhite())
				out.push_back(cPos);
			return true;
		}
		
		return false;
	}
	return true;
}

void CrossMove::validMoves(std::vector<Pos>& out, Piece* from)
{
	Log log(2);
	Pos origin = from->getPos();
	Board* game = from->getBoard();
	bool stopTR = false;
	bool stopTL = false;
	bool stopBR = false;
	bool stopBL = false;
	
	for(int i = 1; i < 8; i++)
	{
		if(!stopTL)
		{
			Pos cPos(origin);
			cPos.setX(cPos.getX() - i);
			cPos.setY(cPos.getY() - i);
			stopTL = checkPosition(origin, cPos, out, from, game);
		}
		
		if(!stopTR)
		{
			Pos cPos(origin);
			cPos.setX(cPos.getX() + i);
			cPos.setY(cPos.getY() - i);
			stopTR = checkPosition(origin, cPos, out, from, game);
		}
		
		if(!stopBR)
		{
			Pos cPos(origin);
			cPos.setX(cPos.getX() + i);
			cPos.setY(cPos.getY() + i);
			stopBR = checkPosition(origin, cPos, out, from, game);
		}
		
		if(!stopBL)
		{
			Pos cPos(origin);
			cPos.setX(cPos.getX() - i);
			cPos.setY(cPos.getY() + i);
			stopBL = checkPosition(origin, cPos, out, from, game);
		}
		
		if(stopTR && stopTL && stopBR && stopBL)
			break;
	}
	
	// logging, all possible moves are logged at level 2
	log.append("CROSS VALID MOVE: VArr " + std::to_string(out.size()) + ":");
	for (auto &x : out)
		log.append(x.toString() + ", ");
	log.setLogLevel(1);
	log.append(" trn: " + std::to_string(game->getTurnFEN()) + "total moves: " + std::to_string(game->getMoves()) + "\n");
}

bool CrossMove::isValidMove(const Pos& to, Piece* from)
{
	std::vector<Pos> templist;
	validMoves(templist, from);
	for(long unsigned int i = 0; i < templist.size(); i++)
		if(templist[i] == to)
			return true;
	return false;
}