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
	
	bool operator[](int) const; // get the value of a single position in the bitboard
	bool operator[](Pos) const; // get the value of a single position in the bitboard
	
    Bitboard operator|(const Bitboard&) const;
    Bitboard operator&(const Bitboard&) const;
    Bitboard operator^(const Bitboard&) const;
    Bitboard operator~() const;

    bool operator==(const Bitboard&) const;
    bool operator!=(const Bitboard&) const;

	private:
    uint64_t value;

};



#endif