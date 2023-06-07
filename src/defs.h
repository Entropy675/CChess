#ifndef DEFS_H
#define DEFS_H

#define C_TRUE			1
#define C_FALSE			0
#define C_OK			1
#define C_NOK			-1

#define MAX_ROW_COL		8  // since its a square row and col are same
#define MAX_ARR_SIZE	64 
#define NUM_PIECES		32


#define LOG_LEVEL		2 // LOG LEVEL!

#include <string>

enum class ChessStatus 
{
	FAIL,
	SUCCESS,
	PROMOTE,
	PAWNMOVE
};

inline std::string getChessStatusString(ChessStatus stat) 
{
    switch (stat) {
        case ChessStatus::FAIL:
            return "FAIL";
        case ChessStatus::SUCCESS:
            return "SUCCESS";
        case ChessStatus::PROMOTE:
            return "PROMOTE";
        case ChessStatus::PAWNMOVE:
            return "PAWNMOVE";
    }
    return "UNKNOWN"; // Handle unknown status gracefully
}

// only merge strings of same '\n' newline count, or str1 < str2 '\n's (I lazy, theres probably a better way to write this but I did this in a min)
inline std::string mergeStrings(std::string str2, const std::string& str1) 
{
    std::string mergedString;
	str2 += "\n"; // (the second one needs to be offset by at least one \n)
	
	unsigned long size = str1.size() + str2.size();
	unsigned long str1c = 0;
	unsigned long str2c = 0;
	
	bool flip = false;
	while(str1c + str2c < size)
	{
		char current;
		if(flip)
			current = str1[str1c++];
		else
			current = str2[str2c++];

		if(current == '\n')
		{
			flip = !flip;
			if(flip)
			{
				mergedString += "  ";
				size += 2;
			}
			else
				mergedString += current;
		}
		else
			mergedString += current;
	}

    return mergedString;
}
class ChessGame;

class Board;
class NcView;

class Log;
class Pos;

class Piece;
class Bishop;
class Pawn;
class Knight;
class Queen;
class King;
class Bishop;


#endif
