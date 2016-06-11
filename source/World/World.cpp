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

#include "Backend/Input.hpp"

#include "World.hpp"

// TODO: Change arbitrary value (This is to prevent seg faults from starting left of (0,0))

World::World(const Vector2f &GRAVITY) : blocks(), playerPos(500, 500), camPos(500, 500), GRAVITY(GRAVITY)
{
	generator.generate(*this);
}

void World::update(float dt)
{
	updatePlayer(dt);
	updateCamera(dt);
}

const Vector2f &World::getGravity()
{
	return GRAVITY;
}

void World::updatePlayer(float dt)
{
	float VAL = 600.f * dt;

	if (isKeyPressed(Keys::Left))
		playerPos.x -= VAL;
	if (isKeyPressed(Keys::Right))
		playerPos.x += VAL;
	if (isKeyPressed(Keys::Up))
		playerPos.y -= VAL;
	if (isKeyPressed(Keys::Down))
		playerPos.y += VAL;
}

void World::updateCamera(float dt)
{
	camPos += (playerPos - camPos) * 2.f * dt; // TODO: Remove magic number
}
