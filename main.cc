#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include "defs.h"

int main() 
{
    setlocale(LC_ALL,""); // Set the locale to the user's preferred one
    initscr();
    cbreak();
    noecho();
    
    attron(A_BOLD);
	
	// lets get the size of a square on the screen
	int sqX = 3; // accounting for border
	int sqY = 3;
	
	
	// example setup board
    cchar_t pawn;
    wchar_t pwide = L'♟';
    setcchar(&pawn, &pwide, A_NORMAL, 0, NULL);
    
    cchar_t li;
    wchar_t liwide = L'─';
    setcchar(&li, &liwide, A_NORMAL, 0, NULL);
    
    cchar_t ld;
    wchar_t ldwide = L'│';
    setcchar(&ld, &ldwide, A_NORMAL, 0, NULL);
    
    for(int x = 1; x <= MAX_ROW_COL - 1; x++)
	{
		for(int line = 1; line < sqX*MAX_ROW_COL; line++)
		{
			move(line, sqX*x);
			add_wch(&ld);
		}
	}
	
	for(int y = 1; y <= MAX_ROW_COL - 1; y++)
	{
		move(sqY*y, 1);
		for(int line = 0; line < sqY*MAX_ROW_COL; line++)
			add_wch(&li);
		//move(sqX*x + sqX/2 + 1, sqY*y + sqY/2 + 1);
		//add_wch(&pawn);	
		
	}
	
	for(int x = 1; x <= MAX_ROW_COL -1; x++)
	{
		for(int y = 1; y <= MAX_ROW_COL -1; y++)
		{

		}
	}
	
    
	move(1, 1);
    
    for(int i = 0; i < MAX_ROW_COL; i++)
	    add_wch(&pawn); // Add the pawn character to the current cursor position
	    
	move(2, 1);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
	    add_wch(&pawn); 
	
	move(5, 1);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
	    add_wch(&pawn);
	
	move(6, 1);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
	    add_wch(&pawn);
	    
	    
	mvprintw(7, 1, "Screen size: %dx%d sqaresize: %dx%d", COLS, LINES, sqX, sqY);
	
    refresh();
    getch();
    endwin();

    return 0;
}
/*
int main()
{
	initscr();
	
	printw("Hello world!");
	
	refresh();
	
	getch();
	

	return 0;
}*/
