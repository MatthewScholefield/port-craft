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
#include <SFML/System/Vector2.hpp>
#include "elements/Block.hpp"
#include "../Backend/types.hpp"

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

	//-- Functions --
public:
	World();
	void update(float dT);
private:
	void updatePlayer();
	void updateCamera(float dT);

	//-- Variables --
public:
	static const int NUM_LAYERS = 2;
	static const int WIDTH = WORLD_WIDTH, HEIGHT = WORLD_HEIGHT;
private:
	Array3D<Block, NUM_LAYERS, WIDTH, HEIGHT> blocks;
	sf::Vector2f camPos;
	sf::Vector2f playerPos;
};