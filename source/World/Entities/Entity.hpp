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

#include "Backend/Vector.hpp"
#include "Backend/Graphics/RenderWindow.hpp"

class World;

enum class EntityType
{
	MOB = 0,
	PARTICLE,
	
	LENGTH
};

class Entity
{
public:
	static void init();
	
	Entity(const EntityType ENTITY_TYPE, const Vector2f &pos);
	virtual ~Entity() = default;
	
	void update(float dt, World &world);
	virtual void draw(RenderWindow &window) = 0;
	const Vector2f &getPos() const;
	const Vector2f getPixPos(RenderWindow &window) const;
protected:
	const EntityType ENTITY_TYPE;
	Vector2f pos, vel; // In Blocks and Blocks per Second
	virtual void updatePhysics(float dt, World &world);
private:
	virtual void updateEntity(float dt, World &world) = 0;
};
