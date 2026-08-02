#include "Bitboard.h"

Bitboard::Bitboard(uint64_t value) : value(value) {}

void Bitboard::setBit(Pos p) 
{
	setBit(p.convertToIndex());
}

void Bitboard::setBit(int pos)
{
    value |= (1ULL << pos);
}

void Bitboard::clearBit(Pos p) 
{
	clearBit(p.convertToIndex());
}

void Bitboard::clearBit(int pos) 
{
	value &= ~(1ULL << pos);
}

void Bitboard::clear()
{
	value = 0;
}

std::string Bitboard::toString(bool addSpace) const
{
	std::string r = "";
	if(addSpace)
		r += " ";
	r += " 01234567 \n";
	
	for(int y = 0; y < MAX_ROW_COL; y++)
	{
		r += std::to_string(y) + "|";
		for(int x = 0; x < MAX_ROW_COL; x++)
			r += (*this)[Pos(x,y)] ? 'X' : ' ';
		r += "|\n";
	}
	r += "  01234567 ";
	return r;
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
