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

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "World.hpp"

//#include "Entities/Mobs/Player.hpp"

// TODO: Change arbitrary value (This is to prevent seg faults from starting left of (0,0))

World::World(const Vector2f &GRAVITY) :
blocks(), brightness(), camPos(500, 500), generator(),
GRAVITY(GRAVITY)
{
	generator.generate(*this);
}

/*void World::update(float dt, const Player &player)
{
	updateCamera(dt, player.getPixPos());
}*/

const Vector2f &World::getGravity()
{
	return GRAVITY;
}

const Vector2i World::coordToPix(const Vector2f &POS) const
{
	return (Vector2i)(POS * (float)BLOCK_PX);
}

const Vector2f World::pixToCoord(const Vector2i &POS) const
{
	return (Vector2f) POS / (float)BLOCK_PX;
}

void World::updateCamera(float dt, const Vector2f &pos)
{

	camPos += (pos - camPos) * 2.f * dt; // TODO: Remove magic number
}

Block World::getBlock(Layer layer, int x, int y)
{
	return blocks[layer][x][y];
}

Block World::getBlock(int x, int y)
{
	return getBlock(Layer::FG, x, y);
}

Block World::getBlock(Layer layer, const Vector2u &coord)
{
	return getBlock(layer, coord.x, coord.y);
}

Block World::getBlock(const Vector2u &coord)
{
	return getBlock(Layer::FG, coord.x, coord.y);
}

Block World::getBlock(Layer layer, const Vector2f &coord)
{
	return getBlock(layer, coord.x, coord.y);
}

Block World::getBlock(const Vector2f &coord)
{
	return getBlock(Layer::FG, coord.x, coord.y);
}
