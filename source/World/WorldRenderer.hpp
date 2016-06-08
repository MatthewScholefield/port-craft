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

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "World.hpp"

namespace sf
{
class Color;
class RenderStates;
class RenderTarget;
class Texture;
class View;
}

// Provides fast rendering of tilemaps

class WorldRenderer : public sf::Drawable
{
public:
	WorldRenderer(World &world, const sf::Texture &TEXTURE, unsigned int tileSize = 16, int layers = 1);
	~WorldRenderer(void);
	float getTileSize() const;
	int getLayers() const;

	void refresh();
	void refresh(int x, int y);
	void draw(sf::RenderTarget &rt, sf::RenderStates states) const;
	void update(sf::RenderTarget &rt);
	void update(sf::View &view);
	void calculateBrightness();
private:
	int width;
	int height;
	const int TILE_SIZE;
	const int LAYERS;
	static const int SUB_AMOUNT[16];
	std::vector<sf::Vertex> vertices;
	sf::Vector2i offset;
	const sf::Vector2u NUM_TILES;
	const sf::Texture &TEXTURE;
	World &world;

	void setSize(sf::Vector2f v);
	void setCorner(sf::Vector2f v);
	sf::Vector2i getTile(sf::Vector2f pos) const;
	sf::Vector2u getTile(Block block) const;
	void draw(int index, sf::FloatRect rec, sf::IntRect src, sf::Color color);
	void refreshLocal(int left, int top, int right, int bottom);
	bool isVisible(int x, int y);
	void brightnessUpdate(int x, int y, int brightness);
	void checkBlock(int x, int y);
};