#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <string>
#include <cstring>
#include <regex>
#include <iostream>

#include "defs.h"
#include "Pos.h"
#include "Board.h"
#include "Piece.h"
#include "ChessGame.h"

using namespace std;

ChessGame::ChessGame() : largeBoard(false)
{
	whitePieces = new std::vector<Piece*>;
	blackPieces = new std::vector<Piece*>;
	game = new Board();
	view = new NcView(game, whitePieces, blackPieces);
}

ChessGame::~ChessGame()
{	
	// board cleans up the pieces it holds
	for(long unsigned int i = 0; i < whitePieces->size(); i++)
		delete whitePieces->at(i); // never ever remove pieces from this, just set them dead when they die
		
	for(long unsigned int i = 0; i < blackPieces->size(); i++)
		delete blackPieces->at(i);		
	
	delete whitePieces;
	delete blackPieces;
	
	delete game;
	delete view;
}

void ChessGame::startGame()
{
	game->setStartingBoard(true, whitePieces, blackPieces);
	view->initNcurses();
	view->drawBoard();
	
	mvprintw(19, 1, "Board size: %dx%d sqaresize: %dx%d\n Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.", 
	view->sqSize.getY()*MAX_ROW_COL, view->sqSize.getX()*MAX_ROW_COL, view->sqSize.getX(), view->sqSize.getY());
	
	bool redraw;
	
	while(true)
	{
		move(view->sqSize.getY()*MAX_ROW_COL + 2, 0);
		
		redraw = true;
		
		string uinp;
		view->userInput(uinp);
		
		//addstr(uinp.c_str());
		
		// for valid input, must be of format "c# c#", where c = char in "abcdefgh"
		// could also support p = kqrkbp in format "pc#", where only one valid move can go there.
		// could also support "c#" where only one valid move exists (this is cringe but completely doable)
		
		regex pattern("[a-h][1-8] [a-h][1-8]"); // lets just use regex
		
		if(regex_match(uinp, pattern))
		{
			// this is a valid input 
			Pos p1, p2;
			
			p1.setX(bCharToInt(uinp[0])); // a
			p1.setY(8 - (uinp[1] - '0')); // 1 -> 0
			
			p2.setX(bCharToInt(uinp[3]));
			p2.setY(8 - (uinp[4] - '0'));
			
			printf("\nPOS1 %d %d\n", p1.getX(), p1.getY());
			printf("\nPOS2 %d %d\n", p2.getX(), p2.getY());
			
			game->movePiece(p1, p2); // has access to board, has access to both pieces
		}
		
		regex pattern2("[a-h][1-8]"); // lets just use regex
		
		if(regex_match(uinp, pattern2))
		{
			// this is a valid input for single location given (only one possible valid move)
			
		}
		
		if(uinp == string("tg"))
		{
			view->toggleSize();
			refresh();
		}
		
		else if(uinp == string("exit"))
			break;
			
		if(redraw)
		{
			view->drawBoard();
			refresh();
		}
	}
	
	
	move(0, 0);

	refresh();
	//getch();
	view->cleanupNcurses();
}

// abcdefgh -> 01234567
int ChessGame::bCharToInt(char a)
{
	return a - 'a';
}

