#ifndef DEFS_H
#define DEFS_H
// using preprocessor directive to avoid multiple inclusions of the defs file when it matters

#define MAX_ARR_SIZE	64 // only will ever need max 64 positions in array (8*8 grid)

#define C_TRUE			1
#define C_FALSE			0

#define MAX_ROW_COL		8 // since its a square row and col are same


int bCharToInt(char& a);

class Board;
class Pos;

class Piece;

class Bishop;
class Pawn;
class Knight;
class Queen;
class King;
class Bishop;


#endif
