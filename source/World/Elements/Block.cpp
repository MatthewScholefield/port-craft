#include "Block.hpp"
#include <cassert>
#include <random>

std::array<std::string, Block::LENGTH> Block::names = {
	"Air",
	"Stone",
	"Dirt",
	"Grass",
	"Torch",
	"Pumpkin Light",
	"Glowstone",
	"Log",
	"Oak Wood",
	"Birch Wood",
	"Plank",
	"Leaves",
	"Redwood Leaves",
	"Jungle Leaves",
	"Glass",
	"Cactus",
	"Sand",
	"Bedrock",
	"Snow Top",
	"Snow Grass",
	"Coal Ore",
	"Iron Ore",
	"Gold Ore",
	"Diamond Ore",
	"Redstone Ore",
	"Tnt",
	"Sandstone",
	"Red Flower",
	"Yellow Flower",
	"Iron Block",
	"Gold Block",
	"Diamond Block",
	"Black Wool",
	"Red Wool",
	"Dark Green Wool",
	"Brown Wool",
	"Blue Wool",
	"Purple Wool",
	"Cyan Wool",
	"Gray Wool",
	"White Wool",
	"Dark Gray Wool",
	"Pink Wool",
	"Light Green Wool",
	"Yellow Wool",
	"Light Blue Wool",
	"Fuchsia Wool",
	"Orange Wool",
	"Ladder",
	"Jungle Wood",
	"Jungle Grass",
	"Tall Grass",
	"Shrub",
	"Raw Porkchop",
	"Raw Beef",
	"Leather",
	"Wood Pickaxe",
	"Stone Pickaxe",
	"Iron Pickaxe",
	"Gold Pickaxe",
	"Diamond Pickaxe",
	"Coal",
	"Ingot Iron",
	"Ingot Gold",
	"Diamond",
	"Stick",
	"Flesh",
	"Beef Cooked",
	"Porkchop Cooked",
	"Chicken Raw",
	"Chicken Cooked",
	"Cobblestone",
	"Furnace",
	"Furnace Lit",
	"Crafting Table",
	"Chest",
	"Shovel Diamond",
	"Shovel Wood",
	"Shovel Stone",
	"Shovel Iron",
	"Shovel Gold",
	"Axe Diamond",
	"Axe Wood",
	"Axe Stone",
	"Axe Iron",
	"Axe Gold",
	"Sword Diamond",
	"Sword Wood",
	"Sword Stone",
	"Sword Iron",
	"Sword Gold",
	"Gravel",
	"Mushroom Brown",
	"Mushroom Red",
	"Mushroom Stem",
	"Mushroom Top",
	"Pumpkin",
	"Seeds Pumpkin",
	"Seeds Wheat",
	"Mycelium",
	"Oak Sapling",
	"Jungle Sapling",
	"Spruce Sapling",
	"Top of Open Door",
	"Bottom of Open Door",
	"Top of Closed Door",
	"Bottom of Closed Door",
	"Door",
	"Water",
	"Water Bucket",
	"Empty Bucket",
	"Door",
	"Water Bucket",
	"Bucket"
};

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

const std::string &Block::getName()
{
	return names[id];
}
