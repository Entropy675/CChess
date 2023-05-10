#include "View.h"

int View::nextId = 0;

View::View(Board* g) : id(nextId++), game(g) {}

View::~View(){}

int View::getId() const
{
	return id;
}

void View::subscribeToGame(Board* g)
{
	game = g;
}