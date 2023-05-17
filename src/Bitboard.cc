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

bool Bitboard::operator[](int index) const 
{
	uint64_t mask = 1ULL << index; // 1ULL = 00..01, bit shift to the right to move it to the index pos.
	return (value & mask) != 0; // & between bitmask and value gives value of that pos
}

bool Bitboard::operator[](Pos p) const 
{
	uint64_t mask = 1ULL << p.convertToIndex(); // 1ULL = 00..01, bit shift to the right to move it to the index pos.
	return (value & mask) != 0; // & between bitmask and value gives value of that pos
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
