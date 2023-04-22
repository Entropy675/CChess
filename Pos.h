#ifndef POS_H
#define POS_H

#include <iostream>

class Pos
{
	friend std::ostream& operator<<(std::ostream&, const Pos&);

	public:
	Pos(int x = 0, int y = 0);
	Pos(const Pos&);


	Pos& operator=(const Pos&);
	void set(const Pos p);

	// following return C_NOK for invalid position (else C_OK)
	int set(const int ix, const int iy);
	int setX(const int ix);
	int setY(const int iy);

	int getX() const;
	int getY() const;

	// not defining a < or > for this because its too subjective
	// - the meaning relative to the application is unclear.
	int& operator[](int);

	Pos operator+(const Pos&) const;
	Pos operator-(const Pos&) const;

	bool operator==(const Pos&) const;
	bool operator!=(const Pos&) const;

	Pos& operator+=(const Pos&);
	Pos& operator-=(const Pos&);

	private:
	bool isValid(int ix, int iy) const; // check if the position is valid, for internal use, do not save invalid pos

	int x, y;
};

#endif
