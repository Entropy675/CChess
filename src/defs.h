#ifndef DEFS_H
#define DEFS_H

#define C_TRUE			1
#define C_FALSE			0
#define C_OK			1
#define C_NOK			-1

#define MAX_ROW_COL		8  // since its a square row and col are same
#define MAX_ARR_SIZE	64 
#define NUM_PIECES		32

#include <string>

enum class ChessStatus {
	FAIL,
	SUCCESS,
	PROMOTE,
	PAWNMOVE
};

inline std::string getChessStatusString(ChessStatus stat) {
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
