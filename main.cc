#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <cstring>
#include <regex>

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


	game->setStartingBoard(true);
	game->drawBoard();
	mvprintw(19, 1, "Board size: %dx%d sqaresize: %dx%d\n Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.", game->sqSize.getY()*MAX_ROW_COL, game->sqSize.getX()*MAX_ROW_COL, 
				game->sqSize.getX(), game->sqSize.getY());
	

	
	while(true)
	{
		move(game->sqSize.getY()*MAX_ROW_COL + 2, 0);
		
		string uinp;
		char ch;
		while(true)
		{
			ch = getch();
			addch(ch);
			uinp += ch;
			refresh();
			if(ch == '\n')
				break;
		}
		
		uinp.erase(uinp.end()-1); // null terminates, removes \n from uinp
		//addstr(uinp.c_str());
		
		// for valid input, must be of format "c# c#", where c = char in "abcdefgh"
		// could also support p = kqrkbp in format "pc#", where only one valid move can go there.
		// could also support "c#" where only one valid move exists (this is cringe but completely doable)
		
		regex pattern("[a-h][1-8] [a-h][1-8]"); // lets just use regex
		
		if(regex_match(uinp, pattern))
		{
			// this is a valid input 
			
		}
		regex pattern2("[a-h][1-8]"); // lets just use regex
		
		if(regex_match(uinp, pattern2))
		{
			// this is a valid input for single location given (only one possible valid move)
			
		}
		
		if(uinp == string("tg"))
		{
			game->toggleSize();
			refresh();
		}
		
		else if(uinp == string("exit"))
			break;
			
		game->drawBoard();	
	}
	
	game->cleanBoard();
	
	move(0, 0);

	refresh();
	//getch();
	endwin();
	return 0;
}

int bCharToInt(char& a)
{
	int out = 0;
	
	
	return out;
}




