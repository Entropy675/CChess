#ifndef POS_H
#define POS_H

#include <iostream>
#include <string>

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
