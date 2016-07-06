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

#include <SFML/Graphics/RenderWindow.hpp>

#include "../Vector.hpp"

class WorldRenderer;
class SFMLGraphics;
namespace sf
{
class Drawable;
class RenderStates;
class Vertex;
enum PrimitiveType;
}

class RenderWindow
{
public:
	RenderWindow();
	static float calcZoom(Vector2f size);
	void updateInternal(SFMLGraphics &textureManager);
	const Vector2f &getSize();
	float getScale();
	bool isOpen();
	void clear();
	void display();
	void updateRenderer(WorldRenderer &renderer);
	void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
	void draw(const sf::Vertex* vertices, std::size_t vertexCount,
              sf::PrimitiveType type, const sf::RenderStates& states = sf::RenderStates::Default);
	Vector2i mapCoordsToPixel(Vector2f pos);
	
	sf::RenderWindow &getWindow()
	{
		return window;
	}

private:
	sf::RenderWindow window;
	sf::View view;

	Vector2f origSize;
	float zoomFactor;
};
