/*
 * Copyright (C) 2016 Matthew D. Scholefield
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) anplayerPos.y later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warrantplayerPos.y of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copplayerPos.y of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <array>
#include "Elements/Block.hpp"
#include "Generator/WorldGenerator.hpp"

#include "Backend/Vector.hpp"
#include "Backend/types.hpp"

class Player;

class World
{
	friend class WorldGenerator;
	friend class WorldRenderer;

	//-- Types --
public:

	enum Layer
	{
		BG = 0,
		FG = 1
	};
private:
	template <class T, unsigned I, unsigned J, unsigned K>
	using Array3D = std::array<std::array<std::array<T, K>, J>, I>;

	template <class T, unsigned I, unsigned J>
	using Array2D = std::array<std::array<T, J>, I>;

	//-- Functions --
public:
	World(const Vector2f &GRAVITY);
	//void update(float dT, const Player &player); TODO: Implement player on DS, and uncomment this
	const Vector2f &getGravity();
//private: TODO: Implement player on DS, and uncomment this
	void updateCamera(float dT, const Vector2f &pos);
	Block getBlock(Layer layer, int x, int y);
	Block getBlock(int x, int y);
	Block getBlock(Layer layer, const Vector2u &coord);
	Block getBlock(const Vector2u &coord);
	
	Block getBlock(Layer layer, const Vector2f &coord);
	Block getBlock(const Vector2f &coord);

	//-- Variables --
public:
	static const int NUM_LAYERS = 2;
	static const int WIDTH = WORLD_WIDTH, HEIGHT = WORLD_HEIGHT;
	Array3D<Block, NUM_LAYERS, WIDTH, HEIGHT> blocks;
	Array2D<int, WIDTH, HEIGHT> brightness;
private:
	Vector2f camPos;
	WorldGenerator generator;
	Vector2f GRAVITY;
};
