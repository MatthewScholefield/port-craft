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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "SFMLGraphics.hpp"

SFMLGraphics::SFMLGraphics(const sf::Vector2f &SIZE) : rectangle({})
{
	resize(SIZE);
}

SFMLGraphics::SFMLGraphics(const SFMLGraphics& orig) { }

SFMLGraphics::~SFMLGraphics() { }

bool SFMLGraphics::loadTexture()
{
	if (!image.loadFromFile("gfx/blocks.png"))
		return false;
	image.createMaskFromColor(sf::Color(255, 0, 255));
	texture.loadFromImage(image);
	texture.setSmooth(false);
	return true;
}

void SFMLGraphics::resize(const sf::Vector2f &SIZE)
{
	sf::Color skyColors[2] = {
		{10, 30, 100},
		{30, 110, 190}
	};
	std::array<sf::Vertex, 4> temp = {
		{
			{sf::Vector2f(0, 0), skyColors[0]},
			{sf::Vector2f(SIZE.x + 1, 0), skyColors[0]},
			{sf::Vector2f(SIZE.x + 1, SIZE.y + 1), skyColors[1]},
			{sf::Vector2f(0, SIZE.y + 1), skyColors[1]}
		}
	};
	rectangle = temp;
}

sf::Texture &SFMLGraphics::getTexture()
{
	return texture;
}

void SFMLGraphics::drawSky(sf::RenderWindow &window)
{
	std::array<sf::Vertex, 4> temp(rectangle);
	const sf::Vector2f &pos = (sf::Vector2f)window.mapCoordsToPixel(sf::Vector2f(0, 0));
	for (auto &i : temp)
	{
		i.position -= pos;
	}
	
	window.draw(temp.data(), 4, sf::Quads);
}
