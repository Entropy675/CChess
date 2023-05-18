#ifndef POS_H
#define POS_H

#include <iostream>
#include <string>
#include "defs.h"


// The Pos class only holds valid positions on the chess board. Attempting to add or change to an
// invalid position will result in no change. Initializing a new object with an invalid position returns 
// a Pos object of the position 0,0. Beware, do not use Pos to hold invalid positions even temporarily. 
// If something is ending up on the top left corner for no reason, its defaulting because the value its
// initialized with is invalid.
class Pos
{
	friend std::ostream& operator<<(std::ostream&, const Pos&);

	public:
	Pos(int x = 0, int y = 0);
	Pos(const Pos&);


	Pos& operator=(const Pos&);
	void set(const Pos p);
	static bool isValid(int ix, int iy); // check if the position is valid, this class cannot store an invalid pos

	// following return C_NOK for invalid position (else C_OK)
	int set(const int ix, const int iy);
	int setX(const int ix);
	int setY(const int iy);

	int getX() const;
	int getY() const;

	int convertToIndex() const;

	std::string toString() const;
	
	// not defining a < or > for this because its too subjective
	// - the meaning relative to the application is unclear.
	int& operator[](int);
	int operator[](int) const;

	Pos operator+(const Pos&) const;
	Pos operator-(const Pos&) const;

	bool operator==(const Pos&) const;
	bool operator!=(const Pos&) const;

	Pos& operator+=(const Pos&);
	Pos& operator-=(const Pos&);

	private:

	int x, y;
};

#endif
