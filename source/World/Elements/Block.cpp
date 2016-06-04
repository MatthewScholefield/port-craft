#include "Block.hpp"
#include <cassert>

// TODO: Remove debug

Block::Block() : id(rand() % LENGTH / 2) { }

Block::Block(int id) : id(id) { }

Block::operator int() const
{
	return id;
}

Block &Block::operator=(int val)
{
	assert(val >= 0 && val < LENGTH);
	id = val;
	return *this;
}