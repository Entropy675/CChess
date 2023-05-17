#ifndef BITBOARD
#define BITBOARD

#include <cstdint>
#include "Pos.h"

class Bitboard 
{
	public:
    Bitboard(uint64_t = 0);

    void setBit(Pos p);
    void setBit(int pos);
	void clearBit(int pos);
	
    Bitboard operator|(const Bitboard& other) const;
    Bitboard operator&(const Bitboard& other) const;
    Bitboard operator^(const Bitboard& other) const;
    Bitboard operator~() const;

    bool operator==(const Bitboard& other) const;
    bool operator!=(const Bitboard& other) const;

	private:
    uint64_t value;

};



#endif