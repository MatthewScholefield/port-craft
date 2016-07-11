/*
 * Copyright (C) 2016 Matthew D. Scholefield
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>
#include <memory>

class Block
{
public:
	explicit operator int() const;
	Block &operator=(int val);
	bool operator==(Block block);
	bool operator!=(Block block);
	Block();
	Block(int id);
	
	bool isWalkThrough();
	const std::string &getName();
	
private:
	int id;
public:
	enum
	{
		AIR = 0,
		STONE,
		DIRT,
		GRASS,
		TORCH,
		LIGHT_PUMPKIN,
		GLOWSTONE,
		LOG_OAK,
		LOG_SPRUCE,
		LOG_BIRCH,
		PLANKS_WOOD,
		LEAVES_OAK,
		LEAVES_SPRUCE,
		LEAVES_JUNGLE,
		GLASS,
		CACTUS,
		SAND,
		BEDROCK,
		SNOW_TOP,
		GRASS_SNOW,
		ORE_COAL,
		ORE_IRON,
		ORE_GOLD,
		ORE_DIAMOND,
		ORE_REDSTONE,
		TNT,
		SANDSTONE,
		FLOWER_RED,
		FLOWER_YELLOW,
		BLOCK_IRON,
		BLOCK_GOLD,
		BLOCK_DIAMOND,
		WOOL_BLACK,
		WOOL_RED,
		WOOL_GREEN_DARK,
		WOOL_BROWN,
		BlUE_WOOL,
		WOOL_PURPLE,
		WOOL_CYAN,
		WOOL_GRAY,
		WOOL_WHITE,
		DARK_GRAY_WOOL,
		WOOL_PINK,
		WOOL_GREEN_LIGHT,
		WOOL_YELLOW,
		LIGHT_BLUE_WOOL,
		WOOL_MAGENTA,
		WOOL_ORANGE,
		LADDER,
		LOG_JUNGLE,
		GRASS_JUNGLE,
		TALL_GRASS,
		SHRUB,
		PORKCHOP_RAW,
		BEEF_RAW,
		LEATHER,
		PICKAXE_WOOD,
		PICKAXE_STONE,
		PICKAXE_IRON,
		PICKAXE_GOLD,
		PICKAXE_DIAMOND,
		COAL,
		INGOT_IRON,
		INGOT_GOLD,
		DIAMOND,
		STICK,
		FLESH,
		PORKCHOP_COOKED,
		BEEF_COOKED,
		CHICKEN_RAW,
		CHICKEN_COOKED,
		COBBLESTONE,
		FURNACE,
		FURNACE_LIT,
		CRAFTING_TABLE,
		CHEST,
		SHOVEL_DIAMOND,
		SHOVEL_WOOD,
		SHOVEL_STONE,
		SHOVEL_IRON,
		SHOVEL_GOLD,
		AXE_DIAMOND,
		AXE_WOOD,
		AXE_STONE,
		AXE_IRON,
		AXE_GOLD,
		SWORD_DIAMOND,
		SWORD_WOOD,
		SWORD_STONE,
		SWORD_IRON,
		SWORD_GOLD,
		GRAVEL,
		MUSHROOM_BROWN,
		MUSHROOM_RED,
		MUSHROOM_STEM,
		MUSHROOM_TOP,
		PUMPKIN,
		SEEDS_PUMPKIN,
		SEEDS_WHEAT,
		MYCELIUM,
		SAPLING_OAK,
		SAPLING_JUNGLE,
		SAPLING_SPRUCE,
		DOOR_OPEN_TOP,
		DOOR_OPEN_BOTTOM,
		DOOR_CLOSED_TOP,
		DOOR_CLOSED_BOTTOM,
		DOOR_ITEM,
		WATER,
		BUCKET_WATER,
		BUCKET_EMPTY,

		LENGTH
	};
	
private:
	static std::array<std::string, LENGTH> names;
};
