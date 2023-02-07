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

ChessGame::ChessGame()
{
	game = new Board();
	
	setcchar(&li, L"─", A_NORMAL, 0, NULL);
	setcchar(&ld, L"│", A_NORMAL, 0, NULL);

	if(largeBoard)
	{
		game->sqSize.set(6, 4);
		game->offset.set(3, 2); // from top left corner of square		
	}
	else
	{
		game->sqSize.set(2, 2); // more tight fitting board
		game->offset.set(1, 1); 
	}
}


void ChessGame::startGame()
{
	setlocale(LC_ALL,""); // Set the locale to the user's preferred one
	initscr();
	cbreak();
	noecho();

	attron(A_BOLD);


	game->setStartingBoard(true);
	drawBoard();
	mvprintw(19, 1, "Board size: %dx%d sqaresize: %dx%d\n Use ([Ctrl +] or [Ctrl Shift =]) and [Ctrl -] to resize console on Linux.", game->sqSize.getY()*MAX_ROW_COL, game->sqSize.getX()*MAX_ROW_COL, 
				game->sqSize.getX(), game->sqSize.getY());
	
	
	bool redraw;
	
	while(true)
	{
		move(game->sqSize.getY()*MAX_ROW_COL + 2, 0);
		
		redraw = true;
		
		string uinp;
		userInput(uinp);
		
		uinp.erase(uinp.end()-1); // null terminates, removes \n from uinp
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
			toggleSize();
			refresh();
		}
		
		else if(uinp == string("exit"))
			break;
			
		if(redraw)
		{
			drawBoard();
			refresh();
		}
	}
	
	
	move(0, 0);

	refresh();
	//getch();
	endwin();
}

// abcdefgh -> 01234567
int ChessGame::bCharToInt(char& a)
{
	return a - 'a';
}


void ChessGame::toggleSize()
{
	largeBoard = !largeBoard;
	
	if(largeBoard)
	{
		game->sqSize.set(6, 4);
		game->offset.set(3, 2); // from top left corner of square		
		//sqSize.set(6, 3);
		//offset.set(3, 1); // from top left corner of square		
	}
	else
	{

		game->sqSize.set(2, 2); // more tight fitting board
		game->offset.set(1, 1); 
	}
	
	drawBoard();
}


void ChessGame::userInput(std::string& uinp)
{
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
}

void ChessGame::drawBoard()
{
	clear(); // clear displayed board
	
	//game->getGameBoard()
	for(int x = 0; x <= MAX_ROW_COL; x++)
	{
		for(int line = 1; line < game->sqSize.getY()*MAX_ROW_COL; line++)
		{
			move(line, game->sqSize.getX()*x);
			add_wch(&ld);
		}
	}

	for(int y = 0; y <= MAX_ROW_COL; y++)
	{
		move(game->sqSize.getY()*y, 1);
		for(int line = 0; line < game->sqSize.getX()*MAX_ROW_COL - 1; line++)
			add_wch(&li);
	}

	for(int y = 1; y <= MAX_ROW_COL -1; y++)
	{
		for(int x = 1; x <= MAX_ROW_COL -1; x++)
		{
			move(game->sqSize.getY()*y, game->sqSize.getX()*x);
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
			move(x*game->sqSize.getY() + game->offset.getY(), y*game->sqSize.getX() + game->offset.getX());
			if(game->gameBoard[x][y] != nullptr)
				add_wch(&(((Piece*)game->gameBoard[x][y])->chr));
		}
		int y1 = getcury(stdscr);
		move(y1, game->sqSize.getX()*MAX_ROW_COL + 2);
		addstr((std::to_string(MAX_ROW_COL - x)).c_str());
	}
	
	move(game->sqSize.getY()*MAX_ROW_COL + 1, 0);
	
	const char chars[9] = "abcdefgh";
	
	for(int y = 0; y < MAX_ROW_COL; y++)
	{
		// works well with largeboard 
		for(int i = 0; i < game->sqSize.getX()/2; i++)
			addstr(" ");
			
		addch(chars[y]);
		
		for(int i = 0; i < game->sqSize.getX()/2 - 1; i++)
			addstr(" ");
	}
	
	
	// draw the dead pieces in 2 different lines for white and black
	move(game->sqSize.getY()*MAX_ROW_COL + 3, 0);
	
	for(long unsigned int i = 0; i < NUM_PIECES/2; i++)
		if(game->whitePieces.at(i)->dead == true)
			add_wch(&game->whitePieces.at(i)->chr);
	
	addch('\n');
	
	for(long unsigned int i = 0; i < NUM_PIECES/2; i++)
		if(game->blackPieces.at(i)->dead == true)
			add_wch(&game->blackPieces.at(i)->chr);
}


