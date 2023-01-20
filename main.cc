#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <cstring>
#include "defs.h"
#include "Pos.h"
#include "Board.h"

using namespace std;

int main() 
{
	setlocale(LC_ALL,""); // Set the locale to the user's preferred one
	initscr();
	cbreak();
	noecho();

	attron(A_BOLD);

	
	Board* game = new Board();


	game->drawBoard();
	mvprintw(25, 1, "Board size: %dx%d sqaresize: %dx%d", game->sqSize.getY()*MAX_ROW_COL, game->sqSize.getX()*MAX_ROW_COL, 
				game->sqSize.getX(), game->sqSize.getY());
	

	
	while(true)
	{
		
		move(game->sqSize.getY()*MAX_ROW_COL + 1, 0);
		string uinp; // overflow issues lmao
		char ch;
		while(true)
		{
			ch = getch();
			addch(ch);
			uinp += ch;
			refresh();
			if(ch == '\n')
			{
				break;
			}
		}
		
		uinp.erase(uinp.end()-1); // null terminates, removes \n from uinp
		//addstr(uinp.c_str());
		
		if(uinp == string("tg"))
		{
			game->toggleSize();
			refresh();
		}
		else if(uinp == string("exit"))
			break;
			
		clear();
		game->drawBoard();	
	}
	
	
	move(0, 0);

	refresh();
	//getch();
	endwin();
	return 0;
}






