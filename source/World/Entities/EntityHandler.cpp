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

#include "EntityHandler.hpp"
#include "Mob.hpp"
#include "Mobs/Player.hpp"

EntityHandler::EntityHandler() : entityVectors() { }

void EntityHandler::update(float dt, World& world)
{
	for (auto &vec : entityVectors)
		for (auto &entity : vec)
			entity->update(dt, world);
}

void EntityHandler::draw(RenderWindow &window, World& world)
{
	for (auto &vec : entityVectors)
		for (auto &entity : vec)
			entity->draw(window, world);
}

const Player &EntityHandler::createPlayer()
{
	entityVectors[(int)EntityType::MOB].emplace_back(new Player(Vector2f(10,0)));
	return *((Player*)entityVectors[(int)EntityType::MOB].back());
}