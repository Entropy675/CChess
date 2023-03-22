#include "defs.h"
#include "Pos.h"

Pos::Pos(const int ix, const int iy)
{
	set(ix, iy);
}

Pos::Pos(const Pos& o)
{
	set(o.x, o.y);
}

bool Pos::isValid(const int ix, const int iy) const
{
	if(ix >= MAX_ROW_COL || ix < 0 || iy >= MAX_ROW_COL || iy < 0)
		return false;
	return true;
}

int Pos::set(const int ix, const int iy)
{
	if(!isValid(ix,iy))
		return C_NOK;
	x = ix;
	y = iy;
	return C_OK;
}

void Pos::set(const Pos p)
{
	x = p.x;
	y = p.y;
}

int Pos::setX(const int ix)
{
	if(!isValid(ix,y))
		return C_NOK;
	x = ix;
	return C_OK;
}

int Pos::setY(const int iy)
{
	if(!isValid(x,iy))
		return C_NOK;
	y = iy;
	return C_OK;
}

int Pos::getX() const
{
	return x;
}

int Pos::getY() const
{
	return y;
}

bool Pos::operator==(const Pos &p) const
{
	return x == p.x && y == p.y;
}

bool Pos::operator!=(const Pos &p) const
{
	return !(*this == p);
}

Pos& Pos::operator+=(const Pos &p)
{
	x += p.x;
	y += p.y;
	return *this;
}







