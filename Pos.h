#ifndef POS_H
#define POS_H

#include <iostream>

class Pos
{
	public:
	Pos(int x = 0, int y = 0);
	Pos(const Pos& o);

	void set(const Pos p);

	// following return C_NOK for invalid position (else C_OK)
	int set(const int ix, const int iy);
	int setX(const int ix);
	int setY(const int iy);

	int getX() const;
	int getY() const;

	bool operator==(const Pos &p) const;
	bool operator!=(const Pos &p) const;
	Pos& operator+=(const Pos &p);

	private:
	bool isValid(int ix, int iy) const; // check if the position is valid, for internal use, do not save invalid pos

	int x, y;
};

#endif
