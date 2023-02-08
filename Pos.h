#ifndef POS_H
#define POS_H

#include <iostream>

class Pos
{
	public:

	Pos(int x = 0, int y = 0);


	void set(Pos p);
	
	// following return C_NOK for invalid position (else C_OK)
	int set(int ix, int iy);
	int setX(int ix);
	int setY(int iy);

	int getX();
	int getY();
	
	bool operator==(const Pos &p);
	bool operator!=(const Pos &p);
    
	private:
	bool isValid(int ix, int iy); // check if the position is valid, for internal use, do not save invalid pos

	int x, y;
};

#endif
