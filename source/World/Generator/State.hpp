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

#include "ObjectChooser.hpp"
#include "../Elements/Biome.hpp"
class Block;

class State
{
public:
	virtual void enter();
	virtual State *update(float noise, float threshold, Biome biome);
	virtual Block getBlock() = 0;

	static State *air, *grass, *snowGrass, *dirt, *stone;
protected:
	virtual State *updateVirtual(float noise, Biome biome) = 0;
};

class AirState : public State
{
public:
	State *updateVirtual(float noise, Biome biome);
	Block getBlock();
};

class GrassState : public State
{
public:
	State *updateVirtual(float noise, Biome biome);
	Block getBlock();
};

class SnowGrassState : public State
{
public:
	State *updateVirtual(float noise, Biome biome);
	Block getBlock();
};

class DirtState : public State
{
public:
	void enter();
	State *updateVirtual(float noise, Biome biome);
	Block getBlock();
private:
	int count;
	const int NUM_DIRT = 7;
};

class StoneState : public State
{
public:
	State *updateVirtual(float noise, Biome biome);
	Block getBlock();
private:
	ObjectChooser < Block,
	Entry < Block::STONE, 90 >,
	Entry < Block::ORE_COAL, 10 >,
	Entry < Block::ORE_IRON, 5 >,
	Entry < Block::ORE_GOLD, 3 >,
	Entry < Block::ORE_REDSTONE, 4 >,
	Entry < Block::ORE_DIAMOND, 1 >
	> STONES;
};