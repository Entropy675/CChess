#include "Board.h"
#include "Pos.h"
#include "defs.h"
#include <ncurses.h>
#include <locale.h>
#include <wchar.h>

Board::Board()
{
	
	if(largeBoard)
	{
		sqSize.set(6, 3);
		offset.set(3, 1); // from top left corner of square		
	}
	else
	{
		sqSize.set(2, 2); // more tight fitting board
		offset.set(1, 1); 
	}
}

void Board::toggleSize()
{
	largeBoard = !largeBoard;
	
	if(largeBoard)
	{
		sqSize.set(6, 3);
		offset.set(3, 1); // from top left corner of square		
	}
	else
	{

		sqSize.set(2, 2); // more tight fitting board
		offset.set(1, 1); 
	}
	
	clear();
	drawBoard();
}

void Board::drawBoard()
{
	cchar_t li;
	wchar_t liwide = L'─';
	setcchar(&li, &liwide, A_NORMAL, 0, NULL);

	cchar_t ld;
	wchar_t ldwide = L'│';
	setcchar(&ld, &ldwide, A_NORMAL, 0, NULL);

	for(int x = 0; x <= MAX_ROW_COL; x++)
	{
		for(int line = 1; line < sqSize.getY()*MAX_ROW_COL; line++)
		{
			move(line, sqSize.getX()*x);
			add_wch(&ld);
		}
	}

	for(int y = 0; y <= MAX_ROW_COL; y++)
	{
		move(sqSize.getY()*y, 1);
		for(int line = 0; line < sqSize.getX()*MAX_ROW_COL - 1; line++)
			add_wch(&li);
		//move(sqX*x + sqX/2 + 1, sqY*y + sqY/2 + 1);
		//add_wch(&pawn);	
		
	}

	for(int x = 1; x <= MAX_ROW_COL -1; x++)
	{
		for(int y = 1; y <= MAX_ROW_COL -1; y++)
		{
			move(sqSize.getY()*y, sqSize.getX()*x);
			addstr("+");
		}
	}
	
	// example setup board
	// puts pawns in every position, temporary
	cchar_t pawn;
	wchar_t pwide = L'♟';
	setcchar(&pawn, &pwide, A_NORMAL, 0, NULL);
	
	for(int x = 0; x < MAX_ROW_COL; x++)
	{
		for(int y = 0; y < MAX_ROW_COL; y++)
		{
			move(x*sqSize.getY() + offset.getY(), y*sqSize.getX() + offset.getX());
			add_wch(&pawn);
		}
	}
	
	move(sqSize.getY()*MAX_ROW_COL + 1, 0);
}


