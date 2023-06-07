#include "NcView.h"

/*
** NcView
** Ncurses based implementation of the View class. This is the main dev version
*/
NcView::NcView(Board* g) : View(g), baseWriteHead(19), writeHead(baseWriteHead), logfile("log.txt"), logstring("")
{
	initNcurses();
	setcchar(&li, L"─", A_NORMAL, 0, NULL);
	setcchar(&ld, L"│", A_NORMAL, 0, NULL);

	if(largeBoard)
	{
		sqSize.set(6, 4);
		offset.set(3, 2); // from top left corner of square		
	}
	else
	{
		sqSize.set(4, 2); // SQUARE board, visually clearer
		offset.set(2, 1); 
	}
	
	if(LOG_LEVEL != 0)
		logwin = newwin(logwinHeight, logwinWidth, logwinY, logwinX); // for logging (size of logger is first 2#, second 2 are position.)
	logfile << "============= NEW GAME =============" << std::endl;
}

NcView::~NcView()
{
	if(LOG_LEVEL != 0)
		delwin(logwin);
	cleanupNcurses();
	logfile.close(); 
}

void NcView::toggleSize()
{
	largeBoard = !largeBoard;
	
	if(largeBoard)
	{
		sqSize.set(6, 4);
		offset.set(3, 2);  // from top left corner of square	
		logwinX += 16;
		logwinHeight += 15;
		wresize(logwin, logwinHeight, logwinWidth);
		mvwin(logwin, logwinY, logwinX);
	}
	else
	{

		sqSize.set(4, 2); // more tight fitting board
		offset.set(2, 1); 
		logwinX -= 16;
		logwinHeight -= 15;
		wresize(logwin, logwinHeight, logwinWidth);
		mvwin(logwin, logwinY, logwinX);
	}
	
	update();
}

void NcView::initNcurses()
{
	setlocale(LC_ALL,""); // Set the locale to the user's preferred one
	initscr();
	cbreak();
	noecho();

	attron(A_BOLD);
}

void NcView::cleanupNcurses()
{
	endwin();
}

void NcView::userInput(std::string& uinp)
{
	char ch; // TODO: add backspace functionality 
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
}

void NcView::update()
{
	clear();
	
	drawBoard();
	drawPieces();
	drawPieceBar();
	writeHead = baseWriteHead;
	refresh();
	
	if(LOG_LEVEL == 0)
	{
		moveToInputPos();
		return;
	}
	
	wclear(logwin);
	mvwprintw(logwin, 1, 2, "=== LOG ===\n  %s", logstring.c_str());
	box(logwin, 0, 0);
	wrefresh(logwin);
	moveToInputPos();
}

void NcView::log(const std::string& sin)
{
	std::string s(sin);
	std::size_t pos = 0;
	while ((pos = s.find('\n', pos)) != std::string::npos) {
		s.replace(pos, 1, "\n  ");
		pos += 3; // move past the newly inserted characters
	}
	
	if(logfile.is_open())
	{
		logfile << s << std::endl;
	}
	
	logstring = s;
//	mvwprintw(logwin, 3, 2, "%s", s.c_str());
//	box(logwin, 0, 0);
//	wrefresh(logwin);
}

void NcView::printAt(int x, int y, const std::string& s) const
{
	mvprintw(x, y, "%s", s.c_str());
	moveToInputPos();
}

void NcView::print(const std::string& s)
{
	printAt(writeHead++, 0, s);
}

void NcView::moveToInputPos() const
{
	move(sqSize.getY()*MAX_ROW_COL + 2, 0); // move to position for input
}

void NcView::drawBoard()
{
	// draws an empty labeled board based off sqSize
	for(int x = 0; x <= MAX_ROW_COL; x++)
	{
		for(int line = 1; line < sqSize.getY()*MAX_ROW_COL; line++)
		{
			move(line, sqSize.getX()*x);
			add_wch(&ld); // ld is "─" wide character
		}
	}

	for(int y = 0; y <= MAX_ROW_COL; y++)
	{
		move(sqSize.getY()*y, 1);
		for(int line = 0; line < sqSize.getX()*MAX_ROW_COL - 1; line++)
			add_wch(&li); // li is "│" wide character
	}

	for(int y = 1; y <= MAX_ROW_COL -1; y++)
	{
		for(int x = 1; x <= MAX_ROW_COL -1; x++)
		{
			move(sqSize.getY()*y, sqSize.getX()*x);
			addstr("+");
		}
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
}

void NcView::drawPieces()
{
	// draws all pieces in their right positions based off sqSize and offset
	for(int x = 0; x < MAX_ROW_COL; x++)
	{
		for(int y = 0; y < MAX_ROW_COL; y++)
		{
			Pos p(y, x);
			move(x*sqSize.getY() + offset.getY(), y*sqSize.getX() + offset.getX());
			
			if(!(game->getPiece(p) == nullptr))
			{
				cchar_t ctemp;
				wideChessConversion(game->getPiece(p)->getCharacter(), game->getPiece(p)->isWhite(), ctemp);
				add_wch(&ctemp);
			}
		}
		
		int y1 = getcury(stdscr);
		move(y1, sqSize.getX()*MAX_ROW_COL + 2);
		addstr((std::to_string(MAX_ROW_COL - x)).c_str());
	}
}

void NcView::drawPieceBar()
{
	// draw the dead pieces in 2 different lines for white and black
	move(sqSize.getY()*MAX_ROW_COL + 4, 0);
	cchar_t ctemp;
	
	const char* spaces = "        ";
	
	
	// TODO: refactor these 2 for loops to eliminate getWhitePieces/getBlackPieces if possible
	// or make more functions
	addstr(spaces);
	for(long unsigned int i = 0; i < NUM_PIECES/2; i++)
	{
		if(game->getWhitePieces()->at(i)->isDead())
		{
			wideChessConversion(game->getWhitePieces()->at(i)->getCharacter(), game->getWhitePieces()->at(i)->isWhite(), ctemp);
			add_wch(&ctemp);
		}
	}
	
	wideChessConversion('K', game->isWhiteTurn(), ctemp);
	addstr("\n");
	if(game->isCheckOnBoard())
	{
		if(game->isWhiteTurn())
			addstr("  WHITE ");
		else
			addstr("  BLACK ");
	}
	else 
		addstr(spaces);
	
	addstr("- --<<");
	add_wch(&ctemp);
	add_wch(&ctemp);
	add_wch(&ctemp);
	addstr(">>-- -");
	
	if(game->isCheckOnBoard())
		addstr(" CHECK  ");
	else 
		addstr(spaces);
	addstr("\n");
	
	addstr(spaces);
	for(long unsigned int i = 0; i < NUM_PIECES/2; i++)
	{
		if(game->getBlackPieces()->at(i)->isDead())
		{
			wideChessConversion(game->getBlackPieces()->at(i)->getCharacter(), game->getBlackPieces()->at(i)->isWhite(), ctemp);
			add_wch(&ctemp);
		}
	}
}


void NcView::wideChessConversion(char c, bool isWhite, cchar_t& cch)
{
	wchar_t tmp;
	if(isWhite)
	{
		if(c == 'R')
			tmp = L'♜';
		if(c == 'N')
			tmp = L'♞';
		if(c == 'B')
			tmp = L'♝';
		if(c == 'K')
			tmp = L'♚';
		if(c == 'Q')
			tmp = L'♛';
		if(c == 'P')
			tmp = L'♟';
	}
	else
	{
		if(c == 'R')
			tmp = L'♖';
		if(c == 'N')
			tmp = L'♘';
		if(c == 'B')
			tmp = L'♗';
		if(c == 'K')
			tmp = L'♔';
		if(c == 'Q')
			tmp = L'♕';
		if(c == 'P')
			tmp = L'♙';
	}
	
	setcchar(&cch, &tmp, A_NORMAL, 0, NULL);
}



