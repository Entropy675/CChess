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

int Pos::set(int ix, int iy)
{
	if(!isValid(ix,iy))
		return C_NOK;
	x = ix;
	y = iy;
	return C_OK;
}

void Pos::set(Pos p)
{
	x = p.getX();
	y = p.getY();
}

int Pos::setX(int ix)
{
	if(!isValid(ix,y))
		return C_NOK;
	x = ix;
	return C_OK;
}

int Pos::setY(int iy)
{
	if(!isValid(x,iy))
		return C_NOK;
	y = iy;
	return C_OK;
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






