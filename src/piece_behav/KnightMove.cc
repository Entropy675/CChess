#include "KnightMove.h"

KnightMove::KnightMove() {}
KnightMove::~KnightMove() {}

bool KnightMove::checkPosition(Pos& origin, Pos& cPos, std::vector<Pos>& out, Piece* from, Board* game)
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
			return false;
		}
		return true;
	}
	return false;
}

void KnightMove::validMoves(std::vector<Pos>& out, Piece* from)
{
	Log log(2);
	Pos origin = from->getPos();
	Board* game = from->getBoard();
	
	std::vector<Pos> temp;
	
	Pos cPos(origin);
	cPos.setX(cPos.getX() + 2);
	if(checkPosition(origin, cPos, temp, from, game))
	{
		Pos cTemp = temp.at(temp.size() - 1);
		
		Pos lTemp(cTemp);
		lTemp.setY(lTemp.getY() + 1);
		checkPosition(cTemp, lTemp, out, from, game);
		
		Pos rTemp(cTemp);
		rTemp.setY(rTemp.getY() - 1);
		checkPosition(cTemp, rTemp, out, from, game);
	}
	
	cPos = origin;
	cPos.setX(cPos.getX() - 2);
	if(checkPosition(origin, cPos, temp, from, game))
	{
		Pos cTemp = temp.at(temp.size() - 1);
		
		Pos lTemp(cTemp);
		lTemp.setY(lTemp.getY() + 1);
		checkPosition(cTemp, lTemp, out, from, game);
		
		Pos rTemp(cTemp);
		rTemp.setY(rTemp.getY() - 1);
		checkPosition(cTemp, rTemp, out, from, game);
	}
		
	cPos = origin;
	cPos.setY(cPos.getY() + 2);
	if(checkPosition(origin, cPos, temp, from, game))
	{
		Pos cTemp = temp.at(temp.size() - 1);
		
		Pos lTemp(cTemp);
		lTemp.setX(lTemp.getX() + 1);
		checkPosition(cTemp, lTemp, out, from, game);
		
		Pos rTemp(cTemp);
		rTemp.setX(rTemp.getX() - 1);
		checkPosition(cTemp, rTemp, out, from, game);
	}
	
	cPos = origin;
	cPos.setY(cPos.getY() - 2);
	if(checkPosition(origin, cPos, temp, from, game))
	{
		Pos cTemp = temp.at(temp.size() - 1);
		
		Pos lTemp(cTemp);
		lTemp.setX(lTemp.getX() + 1);
		checkPosition(cTemp, lTemp, out, from, game);
		
		Pos rTemp(cTemp);
		rTemp.setX(rTemp.getX() - 1);
		checkPosition(cTemp, rTemp, out, from, game);
	}
	
	// logging, all possible moves are logged at level 2
	log.append("KNIGHT VALID MOVE: VArr " + std::to_string(out.size()) + ":");
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