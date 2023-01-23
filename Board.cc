#include "Board.h"
#include "Pos.h"
#include "defs.h"

#include "Piece.h"
#include "pieces/Pawn.h"
#include "pieces/King.h"
#include "pieces/Queen.h"
#include "pieces/Knight.h"
#include "pieces/Rook.h"
#include "pieces/Bishop.h"

#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>

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

void Board::setStartingBoard(bool startingColor)
{
	// example setup board
	// puts pawns in every position, temporary
	
	/*
	for(int x = 0; x < MAX_ROW_COL; x++)
	{
		for(int y = 0; y < MAX_ROW_COL; y++)
		{
			// remember to use delete keyword to remove
			gameBoard[x][y] = new Knight(Pos(x, y), x%2 == 0);
		}
	}
	*/
	
	
	// top pieces
	gameBoard[0][0] = new Rook(Pos(0,0), !startingColor);
	gameBoard[0][1] = new Knight(Pos(0,1), !startingColor);
	gameBoard[0][2] = new Bishop(Pos(0,2), !startingColor);
	gameBoard[0][3] = new King(Pos(0,3), !startingColor);
	gameBoard[0][4] = new Queen(Pos(0,4), !startingColor);
	gameBoard[0][5] = new Bishop(Pos(0,5), !startingColor);
	gameBoard[0][6] = new Knight(Pos(0,6), !startingColor);
	gameBoard[0][7] = new Rook(Pos(0,7), !startingColor);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
		gameBoard[1][i] = new Pawn(Pos(1,i), !startingColor);
		
	// bottom pieces
	gameBoard[MAX_ROW_COL-1][0] = new Rook(Pos(MAX_ROW_COL-1,0), startingColor);
	gameBoard[MAX_ROW_COL-1][1] = new Knight(Pos(MAX_ROW_COL-1,1), startingColor);
	gameBoard[MAX_ROW_COL-1][2] = new Bishop(Pos(MAX_ROW_COL-1,2), startingColor);
	gameBoard[MAX_ROW_COL-1][3] = new King(Pos(MAX_ROW_COL-1,3), startingColor);
	gameBoard[MAX_ROW_COL-1][4] = new Queen(Pos(MAX_ROW_COL-1,4), startingColor);
	gameBoard[MAX_ROW_COL-1][5] = new Bishop(Pos(MAX_ROW_COL-1,5), startingColor);
	gameBoard[MAX_ROW_COL-1][6] = new Knight(Pos(MAX_ROW_COL-1,6), startingColor);
	gameBoard[MAX_ROW_COL-1][7] = new Rook(Pos(MAX_ROW_COL-1,7), startingColor);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
		gameBoard[MAX_ROW_COL-2][i] = new Pawn(Pos(MAX_ROW_COL-2,i), startingColor);
	
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

	for(int y = 1; y <= MAX_ROW_COL -1; y++)
	{
		for(int x = 1; x <= MAX_ROW_COL -1; x++)
		{
			move(sqSize.getY()*y, sqSize.getX()*x);
			addstr("+");
		}
	}
	
	// done drawing empty board
	// now drawing pieces
	
	// remember: Piece* gameBoard[MAX_ROW_COL][MAX_ROW_COL];
	// 2d array of piece pointers
	
	for(int x = 0; x < MAX_ROW_COL; x++)
	{
		for(int y = 0; y < MAX_ROW_COL; y++)
		{
			move(x*sqSize.getY() + offset.getY(), y*sqSize.getX() + offset.getX());
			if(gameBoard[x][y] != nullptr)
			{
				add_wch(&(gameBoard[x][y])->chr);
			}
		}
		int y1 = getcury(stdscr);
		move(y1, sqSize.getX()*MAX_ROW_COL + 2);
		addstr((std::to_string(MAX_ROW_COL - x)).c_str());
	}
	
	move(sqSize.getY()*MAX_ROW_COL + 1, 0);
	char chars[9] = "abcdefgh";
	
	for(int y = 0; y < MAX_ROW_COL; y++)
	{
		for(int i = 0; i < sqSize.getX()/2; i++)
			addstr(" ");
			
		addch(chars[y]);
		
		for(int i = 0; i < sqSize.getX()/2 - 1; i++)
			addstr(" ");
			
		// works well with largeboard ... very weird how this works out .... 
	}
	
	//move(sqSize.getY()*MAX_ROW_COL + 2, 0); unnecessary: handled in game loop
}


