#include "ChessGame.h"
#include "NcView.h"

int main() 
{
	View* local = new NcView();
	ChessGame g(local, local); // both players are local view
	g.startLocalNcursesGame();
	delete local;
	return 0;
}


