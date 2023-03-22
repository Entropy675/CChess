#ifndef VIEW_H
#define VIEW_H

#include "Board.h"

/*
** View
** 

*/
class View
{
	public:
	View(Board* g = nullptr);
	virtual ~View();

	virtual void update() = 0;
	virtual void toggleSize() = 0; // large/small
	virtual void userInput(std::string&) = 0;
	virtual void printAt(const Pos& p, const std::string& s) const = 0;
	
	protected:
	Board* game;
	
};


#endif
