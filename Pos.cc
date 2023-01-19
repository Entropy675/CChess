#include "defs.h"
#include "Pos.h"

Pos::Pos(int ix, int iy)
{
	set(ix, iy);
}

bool Pos::isValid(int ix, int iy)
{
	if(ix >= MAX_ROW_COL || ix < 0 || iy >= MAX_ROW_COL || iy < 0)
		return false;
	return true;
}

void Pos::set(int ix, int iy)
{
	if(!isValid(ix,iy))
		return;
	x = ix;
	y = iy;
}

void Pos::setX(int ix)
{
	if(!isValid(ix,y))
		return;
	x = ix;
}

void Pos::setY(int iy)
{
	if(!isValid(x,iy))
		return;
	y = iy;
}

int Pos::getX()
{
	return x;
}

int Pos::getY()
{
	return y;
}

bool Pos::operator==(const Pos &p)
{
	return x == p.x && y == p.y;
}

bool Pos::operator!=(const Pos &p)
{
	return x != p.x && y != p.y;
}






