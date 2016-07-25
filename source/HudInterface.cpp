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

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Backend/Vector.hpp"
#include "SpriteRenderer.hpp"
#include "HudInterface.hpp"
#include "Block.hpp"
#include "RenderWindow.hpp"

HudInterface::HudInterface() : open(false), keyPressed(false) { }

bool HudInterface::isOpen()
{
	return open;
}

void HudInterface::update(Block &selectedBlock, RenderWindow &window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if (!keyPressed)
		{
			keyPressed = true;
			open = !open;
		}
	}
	else
	{
		if (keyPressed)
			keyPressed = false;
	}

	if (open)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Vector2i pos = sf::Mouse::getPosition(window.getWindow());
			pos /= (int)(16.f * window.getScale());
			Block block = pos.y * NUM_COLS + pos.x;
			if (pos.x < NUM_COLS && block.inRange())
				selectedBlock = block;
		}
	}
}

void HudInterface::render(SpriteRenderer &spriteRenderer, RenderWindow &window)
{
	if (!open)
		return;
	int block = Block::AIR;

	for (int renderY = 0; block < Block::LENGTH; ++renderY)
	{
		for (int renderX = 0; block < Block::LENGTH && renderX < NUM_COLS; ++renderX)
		{
			spriteRenderer.renderBlock(renderX, renderY, block, window);
			++block;
		}
	}
}
