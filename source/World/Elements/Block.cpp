#include "Block.hpp"
#include <cassert>
#include <random>

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

bool Block::operator==(Block block)
{
	return block.id == id;
}

bool Block::operator!=(Block block)
{
	return block.id != id;
}

bool Block::isWalkThrough()
{
	switch (id)
	{
	case AIR:
	case FLOWER_YELLOW:
	case FLOWER_RED:
	case SNOW_TOP:
	case TORCH:
	case LADDER:
	case SHRUB:
	case TALL_GRASS:
	case MUSHROOM_BROWN:
	case MUSHROOM_RED:
	case SAPLING_JUNGLE:
	case SAPLING_OAK:
	case SAPLING_SPRUCE:
	case DOOR_OPEN_TOP:
	case DOOR_OPEN_BOTTOM:
	case WATER:
		return true;

	default:
		return false;
	}
}
