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
	setcchar(&li, L"─", A_NORMAL, 0, NULL);
	setcchar(&ld, L"│", A_NORMAL, 0, NULL);

	if(largeBoard)
	{
		sqSize.set(6, 4);
		offset.set(3, 2); // from top left corner of square		
	}
	else
	{
		sqSize.set(2, 2); // more tight fitting board
		offset.set(1, 1); 
	}
}

Board::~Board()
{
	cleanBoard();
}

void Board::toggleSize()
{
	largeBoard = !largeBoard;
	
	if(largeBoard)
	{
		sqSize.set(6, 4);
		offset.set(3, 2); // from top left corner of square		
		//sqSize.set(6, 3);
		//offset.set(3, 1); // from top left corner of square		
	}
	else
	{

		sqSize.set(2, 2); // more tight fitting board
		offset.set(1, 1); 
	}
	
	drawBoard();
}

void Board::movePiece(Pos& a, Pos& b) // move from a to b if valid on this piece
{
	//Piece* aP = gameBoard[a.getY()][a.getX()];
	//Piece* bP = gameBoard[b.getY()][b.getX()];
	
	if(gameBoard[a.getY()][a.getX()] == nullptr)
		return;
	
	// check if valid move, if not then return.
	
	// only do this after checking if the player can actually move to b
	if(gameBoard[b.getY()][b.getX()] != nullptr)
		gameBoard[b.getY()][b.getX()]->dead = true;
	
	gameBoard[a.getY()][a.getX()]->hasMoved = true;
	
	// since our game doesn't rely on the pointers existing on board
	// we can just delete them and forget about them: masterlist of pointers is held in the piece vectors
	gameBoard[b.getY()][b.getX()] = gameBoard[a.getY()][a.getX()];
	gameBoard[a.getY()][a.getX()] = nullptr; 
}

void Board::setStartingBoard(bool startingColor)
{
	// place pieces in their starting positions,
	// populate the vectors corresponding to the black/white pieces.
	
	for(int x = 0; x < MAX_ROW_COL; x++)
	{
		for(int y = 0; y < MAX_ROW_COL; y++)
		{
			gameBoard[y][x] = nullptr;
			
			if((x == 0 || x == MAX_ROW_COL-1) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[y][x] = new Rook(Pos(y,x), (y == 0) ? !startingColor : startingColor);
			else if ((x == 1 || x == MAX_ROW_COL-2) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[y][x] = new Knight(Pos(y,x), (y == 0) ? !startingColor : startingColor);
			else if ((x == 2 || x == MAX_ROW_COL-3) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[y][x] = new Bishop(Pos(y,x), (y == 0) ? !startingColor : startingColor);
			else if ((x == 3) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[y][x] = new Queen(Pos(y,x), (y == 0) ? !startingColor : startingColor);
			else if ((x == 4) && (y == MAX_ROW_COL-1 || y == 0))
				gameBoard[y][x] = new King(Pos(y,x), (y == 0) ? !startingColor : startingColor);
			else if (y == 1 || y == MAX_ROW_COL-2)
				gameBoard[y][x] = new Pawn(Pos(y,x), (y == 1) ? !startingColor : startingColor);
			
			if(y == 0)
				blackPieces.push_back(gameBoard[y][x]);
			else if(y == MAX_ROW_COL-1)
				whitePieces.push_back(gameBoard[y][x]);
		}
	}
	
	for(int i = 0; i < MAX_ROW_COL; i++)
	{
		blackPieces.push_back(gameBoard[1][i]);
		whitePieces.push_back(gameBoard[MAX_ROW_COL-2][i]);
	}

	/* old method
	// top pieces
	gameBoard[0][0] = new Rook(Pos(0,0), !startingColor);
	gameBoard[0][1] = new Knight(Pos(0,1), !startingColor);
	gameBoard[0][2] = new Bishop(Pos(0,2), !startingColor);
	gameBoard[0][3] = new Queen(Pos(0,3), !startingColor);
	gameBoard[0][4] = new King(Pos(0,4), !startingColor);
	gameBoard[0][5] = new Bishop(Pos(0,5), !startingColor);
	gameBoard[0][6] = new Knight(Pos(0,6), !startingColor);
	gameBoard[0][7] = new Rook(Pos(0,7), !startingColor);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
		gameBoard[1][i] = new Pawn(Pos(1,i), !startingColor);
		
	// bottom pieces
	gameBoard[MAX_ROW_COL-1][0] = new Rook(Pos(MAX_ROW_COL-1,0), startingColor);
	gameBoard[MAX_ROW_COL-1][1] = new Knight(Pos(MAX_ROW_COL-1,1), startingColor);
	gameBoard[MAX_ROW_COL-1][2] = new Bishop(Pos(MAX_ROW_COL-1,2), startingColor);
	gameBoard[MAX_ROW_COL-1][3] = new Queen(Pos(MAX_ROW_COL-1,3), startingColor);
	gameBoard[MAX_ROW_COL-1][4] = new King(Pos(MAX_ROW_COL-1,4), startingColor);
	gameBoard[MAX_ROW_COL-1][5] = new Bishop(Pos(MAX_ROW_COL-1,5), startingColor);
	gameBoard[MAX_ROW_COL-1][6] = new Knight(Pos(MAX_ROW_COL-1,6), startingColor);
	gameBoard[MAX_ROW_COL-1][7] = new Rook(Pos(MAX_ROW_COL-1,7), startingColor);
	
	for(int i = 0; i < MAX_ROW_COL; i++)
		gameBoard[MAX_ROW_COL-2][i] = new Pawn(Pos(MAX_ROW_COL-2,i), startingColor);
	*/
}

void Board::cleanBoard()
{
	for(long unsigned int i = 0; i < NUM_PIECES/2; i++)
	{
		delete whitePieces[i]; // never ever remove pieces from this, just set them dead when they die
		delete blackPieces[i];			
	}
}

void Board::userInput(std::string& uinp)
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

void Board::drawBoard()
{
	clear(); // clear board

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
				add_wch(&(gameBoard[x][y])->chr);
		}
		int y1 = getcury(stdscr);
		move(y1, sqSize.getX()*MAX_ROW_COL + 2);
		addstr((std::to_string(MAX_ROW_COL - x)).c_str());
	}
	
	move(sqSize.getY()*MAX_ROW_COL + 1, 0);
	
	const char chars[9] = "abcdefgh";
	
	for(int y = 0; y < MAX_ROW_COL; y++)
	{
		// works well with largeboard 
		for(int i = 0; i < sqSize.getX()/2; i++)
			addstr(" ");
			
		addch(chars[y]);
		
		for(int i = 0; i < sqSize.getX()/2 - 1; i++)
			addstr(" ");
	}
	
	
	// draw the dead pieces in 2 different lines for white and black
	move(sqSize.getY()*MAX_ROW_COL + 3, 0);
	
	for(long unsigned int i = 0; i < NUM_PIECES/2; i++)
		if(whitePieces.at(i)->dead == true)
			add_wch(&whitePieces.at(i)->chr);
	
	addch('\n');
	
	for(long unsigned int i = 0; i < NUM_PIECES/2; i++)
		if(blackPieces.at(i)->dead == true)
			add_wch(&blackPieces.at(i)->chr);
}


