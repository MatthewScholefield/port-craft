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

#include <cassert>

#include <cstdlib>

class Block
{
private:
	int id;

public:

	explicit operator int() const;
	Block &operator=(int val);
	// TODO: change to AIR
	Block();

	Block(int id);

	enum
	{
		AIR = 0,
		STONE,
		DIRT,
		GRASS,
		TORCH,
		PUMPKIN_FACE_ON,
		PUMPKIN_LIGHT,
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
		SNOW_GRASS,
		COAL_ORE,
		ORE_COAL,
		IRON_ORE,
		ORE_IRON,
		GOLD_ORE,
		ORE_GOLD,
		DIAMOND_ORE,
		ORE_DIAMOND,
		REDSTONE_ORE,
		ORE_REDSTONE,
		TNT,
		SANDSTONE,
		ROSE,
		RED_FLOWER,
		FLOWER_RED,
		DANDELION,
		YELLOW_FLOWER,
		FLOWER_YELLOW,
		IRON_BLOCK,
		BLOCK_IRON,
		GOLD_BLOCK,
		BLOCK_GOLD,
		DIAMOND_BLOCK,
		BLOCK_DIAMOND,
		BLACK_WOOL,
		RED_WOOL,
		GREEN_WOOL,
		DARK_GREEN_WOOL,
		BROWN_WOOL,
		BlUE_WOOL,
		PURPLE_WOOL,
		CYAN_WOOL,
		GRAY_WOOL,
		WHITE_WOOL,
		DARK_GRAY_WOOL,
		PINK_WOOL,
		LIME_WOOL,
		LIGHT_GREEN_WOOL,
		YELLOW_WOOL,
		LIGHT_BLUE_WOOL,
		MAGENTA_WOOL,
		ORANGE_WOOL,
		LADDER,
		LOG_JUNGLE,
		GRASS_JUNGLE,
		TALLGRASS,
		TALL_GRASS,
		DEADBUSH,
		SHRUB,
		RAW_PORKCHOP,
		PORKCHOP_RAW,
		RAW_BEEF,
		BEEF_RAW,
		LEATHER,
		WOOD_PICKAXE,
		PICKAXE_WOOD,
		STONE_PICKAXE,
		PICKAXE_STONE,
		IRON_PICKAXE,
		PICKAXE_IRON,
		GOLD_PICKAXE,
		PICKAXE_GOLD,
		DIAMOND_PICKAXE,
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
};