#ifndef POS_H
#define POS_H

class Pos
{
	public:
	
	Pos(x = 0, y = 0);
	
	void set(int ix, int iy);
	void setX(int ix);
	void setY(int iy);
	
	int getX();
	int getY();
	
    bool operator==(const position &p);
    bool operator!=(const position &p);
    
	private:
	bool isValid(); // check if the position is valid, for internal use, do not save invalid pos
	int x, y;
};

#endif
