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

std::ostream& operator<<(std::ostream& o, const Pos& p)
{
	o << "(" << p.x << "," << p.y << ")";
	return o;
}

Pos& Pos::operator=(const Pos& o)
{
	x = o.x;
	y = o.y;
	return *this;
}

int& Pos::operator[](int i)
{
	if(i == 0)
		return x;
	if(i == 1)
		return y; // sorry, but the exception is needed. Cannot return value.
	throw std::out_of_range("Index out of range in Pos::operator[]. Only 0 or 1 allowed.");
}

void Pos::set(const Pos p)
{
	*this = p;
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

bool Pos::operator==(const Pos& p) const
{
	return x == p.x && y == p.y;
}

Pos Pos::operator+(const Pos& a) const
{
	int r1 = x + a.x;
	int r2 = y + a.y;
	return Pos(r1, r2);
}

Pos Pos::operator-(const Pos& a) const
{
	int r1 = x - a.x;
	int r2 = y - a.y;
	return Pos(r1, r2);
}

bool Pos::operator!=(const Pos& p) const
{
	return !(*this == p);
}

Pos& Pos::operator-=(const Pos& p)
{
	x -= p.x;
	y -= p.y;
	return *this;
}

Pos& Pos::operator+=(const Pos& p)
{
	x += p.x;
	y += p.y;
	return *this;
}
