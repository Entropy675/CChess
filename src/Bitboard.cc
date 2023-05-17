#include "Bitboard.h"

Bitboard::Bitboard(uint64_t value) : value(value) {}

void Bitboard::setBit(Pos p) 
{
	int pos = p.convertToIndex();
	setBit(pos);
}

void Bitboard::setBit(int pos)
{
    value |= (1ULL << pos);
}

void Bitboard::clearBit(int pos) 
{
	value &= ~(1ULL << pos);
}

Bitboard Bitboard::operator|(const Bitboard& other) const 
{
	return Bitboard(value | other.value);
}

Bitboard Bitboard::operator&(const Bitboard& other) const 
{
	return Bitboard(value & other.value);
}

Bitboard Bitboard::operator^(const Bitboard& other) const 
{
	return Bitboard(value ^ other.value);
}

Bitboard Bitboard::operator~() const 
{
	return Bitboard(~value);
}

bool Bitboard::operator==(const Bitboard& other) const 
{
	return value == other.value;
}

bool Bitboard::operator!=(const Bitboard& other) const 
{
	return value != other.value;
}
