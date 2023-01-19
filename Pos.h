#ifndef POS_H
#define POS_H

class Pos
{
	public:
	
	Pos(int x = 0, int y = 0);
	
	void set(int ix, int iy);
	void setX(int ix);
	void setY(int iy);
	
	int getX();
	int getY();
	
    bool operator==(const Pos &p);
    bool operator!=(const Pos &p);
    
	private:
	bool isValid(int ix, int iy); // check if the position is valid, for internal use, do not save invalid pos
	int x, y;
};

#endif
