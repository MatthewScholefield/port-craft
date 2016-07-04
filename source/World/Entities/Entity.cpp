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

#include "Entity.hpp"
#include "../World.hpp"
#include "Mobs/Player.hpp"

void Entity::init()
{
	Player::init();
}

Entity::Entity(const EntityType ENTITY_TYPE, const Vector2f &pos) : ENTITY_TYPE(ENTITY_TYPE), pos(pos), vel() { }
// 0 block/s -> 1 block/s in 1 s == 0 
void Entity::update(float dt, World& world)
{
	updatePhysics(dt, world);
	updateEntity(dt, world);
}

void Entity::updatePhysics(float dt, World &world)
{
	vel += world.getGravity() * dt;
	pos += vel * dt;
}

const Vector2f &Entity::getPos() const
{
	return pos;
}

const Vector2f Entity::getPixPos(RenderWindow &window) const
{
	const float BLOCK_PX = 16.f;
	return pos * BLOCK_PX;
}
