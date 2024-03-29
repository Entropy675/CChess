#ifndef VIEW_H
#define VIEW_H

#include "Board.h"

/*
** View
** Virtual class that can be implemented with any graphics library.
** Program will work with any implementation of the View class, allowing for different
** views and different methods of creating views. (Will be useful for web/windows/sockets version later)
** A view must support logging functionality (via the log function).
*/
class View
{
	public:
	View(Board* g = nullptr);
	virtual ~View();

	virtual void update() = 0;
	virtual void toggleSize() = 0; // large/small
	virtual void userInput(std::string&) = 0;
	virtual void print(const std::string&) = 0; // we gonna leave this non-const for compatability :(
	virtual void log(const std::string&) = 0; 
	
	void subscribeToGame(Board*);
	int getId() const;
	
	protected:
	static int nextId;
	int id;
	bool largeBoard = false;
	Board* game;

};


#endif
