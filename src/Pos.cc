#include "defs.h"
#include "Pos.h"

Pos::Pos(const int ix, const int iy) : x(0), y(0)
{
	set(ix, iy);
}

Pos::Pos(const Pos& o)
{
	set(o.x, o.y);
}

bool Pos::isValid(const int ix, const int iy)
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
	o << p.toString();
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

int Pos::operator[](int i) const
{
	if(i == 0)
		return x;
	if(i == 1)
		return y; 
	throw std::out_of_range("Index out of range in Pos::operator[]. Only 0 or 1 allowed.");
}

int Pos::convertToIndex() const
{
    return y * 8 + x;
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

std::string Pos::toString() const
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

bool Pos::operator==(const Pos& p) const
{
	return x == p.x && y == p.y;
}

Pos Pos::operator+(const Pos& a) const
{
	Pos temp(*this);
	temp += a; // utalize validity checking in +=, if invalid this fails, returning a temp with values of this.
	// would be very very bad if this checking did not occur, as the program assumes Pos always holds valid positions.
	return temp;
}

Pos Pos::operator-(const Pos& a) const
{
	Pos temp(*this);
	temp -= a;
	return temp;
}

bool Pos::operator!=(const Pos& p) const
{
	return !(*this == p);
}

Pos& Pos::operator-=(const Pos& p)
{
	this->set(x - p.x, y - p.y);
	//if(this->set(x - p.x, y - p.y) == C_NOK) print some error, but we can kind of just ignore since no change occurs. TODO: log all validity failures in operators with some low log level or something (whatever you do, document it)
	return *this;
}

Pos& Pos::operator+=(const Pos& p)
{
	this->set(x + p.x, y + p.y);
	return *this;
}
