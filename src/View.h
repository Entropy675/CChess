#ifndef VIEW_H
#define VIEW_H

#include "Board.h"

/*
** View
** Virtual class that can be implemented with any graphics library.
** Program will work with any implementation of the View class, allowing for different
** views and different methods of creating views. (Will be useful for web version later)
*/
class View
{
	public:
	View(Board* g = nullptr);
	virtual ~View();

	virtual void update() = 0;
	virtual void toggleSize() = 0; // large/small
	virtual void userInput(std::string&) = 0;
	virtual void printAt(int x, int y, const std::string& s) const = 0;

	protected:
	bool largeBoard = false;
	Board* game;

};


#endif