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

#include <vector>
#include <array>

#include "Entity.hpp"

#include "Backend/Graphics/RenderWindow.hpp"

class World;
class Player;

class EntityHandler
{
public:
	EntityHandler();
	
	void update(float dt, World &world);
	void draw(RenderWindow &window, World &world);
	const Player &createPlayer();
private:
	std::array<std::vector<Entity*>, (int)EntityType::LENGTH> entityVectors;
};
