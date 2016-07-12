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

#include <SFML/Window/Touch.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Backend/Graphics/RenderWindow.hpp"
#include "MiningHandler.hpp"
#include "World.hpp"
#include "SoundManager.hpp"

MiningHandler::MiningHandler() { }

bool MiningHandler::update(World& world, RenderWindow &window, SoundManager &soundManager)
{
	bool changedBlocks = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		Vector2i pos = sf::Mouse::getPosition(window.getWindow());
		Vector2i posScaled = (Vector2i)((Vector2f)pos / window.getScale());
		Vector2i origin = (Vector2i)world.camPos - (Vector2i)window.getSize() / 2;
		Vector2i pPos = posScaled + origin;
		Vector2f coord = world.pixToCoord(pPos);
		
		Block &block = world.blocks[World::FG][(int)coord.x][(int)coord.y];
		if (block != Block::AIR)
		{
			soundManager.playSfx(block, SoundType::DESTROY);
			block = Block::AIR;
		}
		changedBlocks = true;
	}
	
	return changedBlocks;
}
