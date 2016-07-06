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

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Window/Event.hpp>

#include "RenderWindow.hpp"
#include "SFMLGraphics.hpp"
#include "World/WorldRenderer.hpp"

RenderWindow::RenderWindow() :
window(sf::VideoMode(640, 480), "Port Craft", sf::Style::Default),
view(window.getDefaultView()), origSize(view.getSize()), zoomFactor(calcZoom(origSize))
{
	window.setFramerateLimit(60); //TODO: Create option for vsync (for me it causes excessive screen tearing)
	view.zoom(1.f/zoomFactor);
}

float RenderWindow::calcZoom(Vector2f size)
{
	return size.x / 640.f;
}

void RenderWindow::updateInternal(SFMLGraphics &textureManager)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			view.setSize(event.size.width, event.size.height);
			zoomFactor = calcZoom(view.getSize());
			view.zoom(1.f/zoomFactor);
			textureManager.resize(view.getSize());
		}
	}
	window.setView(view);
}

const Vector2f &RenderWindow::getSize()
{
	return view.getSize();
}

float RenderWindow::getScale()
{
	return zoomFactor;
}

bool RenderWindow::isOpen()
{
	return window.isOpen();
}

void RenderWindow::clear()
{
	window.clear();
}

void RenderWindow::display()
{
	window.display();
}

void RenderWindow::updateRenderer(WorldRenderer& renderer)
{
	renderer.update(view);
	renderer.update(window);
}

void RenderWindow::draw(const sf::Drawable& drawable, const sf::RenderStates& states)
{
	window.draw(drawable, states);
}

void RenderWindow::draw(const sf::Vertex* vertices, std::size_t vertexCount,
              sf::PrimitiveType type, const sf::RenderStates& states)
{
	window.draw(vertices, vertexCount, type, states);
}

Vector2i RenderWindow::mapCoordsToPixel(Vector2f pos)
{
	return (Vector2i)(((Vector2f)window.mapCoordsToPixel(pos)) / zoomFactor);
}
