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
#include <SFML/Window/Keyboard.hpp>

#include "Backend/Graphics/RenderWindow.hpp"
#include "MiningHandler.hpp"
#include "World.hpp"
#include "SoundManager.hpp"

MiningHandler::MiningHandler() { }

bool MiningHandler::update(float dt, Block selectedBlock, World& world, RenderWindow &window, SoundManager &soundManager)
{
	bool changedBlocks = false;
	bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (pressed)
	{
		Vector2f pos = window.getMousePos();
		Vector2f origin = world.camPos - window.getSizeUnits() / 2.f;
		Vector2f coord = pos + origin;
		Vector2u touchedCoord = (Vector2u) coord;
		
		if (timeTouched < 0.f || touchedCoord != touched)
		{
			timeTouched = dt;
			touched = touchedCoord;
			finished = false;
		}
		else
			timeTouched += dt;
	}
	if (!finished && (!pressed || timeTouched > ACTIVATE_TIME))
	{
		finished = true;
		Block *block = &world.blocks[World::FG][touched.x][touched.y];
		if (*block != Block::AIR)
		{
			printf("FrontNot\n");
			soundManager.playSfx(*block, SoundType::DESTROY);
			*block = Block::AIR;
		}
		else
		{
			printf("FrontIs\n");
			bool bg = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
			Block *bgBlock = &world.blocks[World::BG][touched.x][touched.y];
			if (*bgBlock == Block::AIR)
			{
				printf("BackIs\n");
				if (bg)
				{
					printf("Bg\n");
					block = bgBlock;
				}
				*block = selectedBlock;
				soundManager.playSfx(selectedBlock, SoundType::PLACE);
			}
			else
			{
				printf("BackNot\n");
				if (bg || timeTouched > ACTIVATE_TIME)
				{
					printf("Activate\n");
					soundManager.playSfx(*bgBlock, SoundType::DESTROY);
					*bgBlock = Block::AIR;
				}
				else
				{
					printf("Short\n");
					*block = selectedBlock;
					soundManager.playSfx(selectedBlock, SoundType::PLACE);
				}
			}
		}
		changedBlocks = true;
		timeTouched = 0.f;
	}
	
	if (!pressed)
	{
		finished = true;
		timeTouched = -1.f;
	}

	return changedBlocks;
}
