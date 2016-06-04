#include "WorldRenderer.hpp"
#include "../Backend/types.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cassert>
#include <iostream>

WorldRenderer::WorldRenderer(const World &WORLD, const sf::Texture &TEXTURE, unsigned int tileSize, int layers)
: WORLD(WORLD), TEXTURE(TEXTURE), TILE_SIZE(tileSize), LAYERS(layers), NUM_TILES(TEXTURE.getSize() / tileSize)
{
	assert(layers > 0);
}

WorldRenderer::~WorldRenderer(void) { }

float WorldRenderer::getTileSize() const
{
	return TILE_SIZE;
}

int WorldRenderer::getLayers() const
{
	return LAYERS;
}

void WorldRenderer::refresh()
{
	refreshLocal(0, 0, width, height);
}

// Redraw part of screen

void WorldRenderer::refreshLocal(int left, int top, int right, int bottom)
{
	for (int y = top; y < bottom; y++)
		for (int x = left; x < right; x++)
			refresh(x + offset.x, y + offset.y);
}

// Adjust amount of vertices to size of the screen

void WorldRenderer::setSize(sf::Vector2f v)
{
	v.x -= 3 * TILE_SIZE; // Verifies the rendered area is correct
	v.y -= 3 * TILE_SIZE; // TODO: Remove debug

	int w = static_cast<int> (v.x / TILE_SIZE) + 2;
	int h = static_cast<int> (v.y / TILE_SIZE) + 2;
	if (w == width && h == height) return;

	width = w;
	height = h;

	int size = width * height * 4 * LAYERS;
	// Allocate quad per tile per layer
	if (vertices.size() < size)
		vertices.resize(width * height * 4 * LAYERS);
	refresh();
}

// Refresh parts of screen if player moved

void WorldRenderer::setCorner(sf::Vector2f v)
{
	v.x += (float) TILE_SIZE; // Verifies the rendered area is correct
	v.y += (float) TILE_SIZE; // TODO: Remove debug
	auto tile = getTile(v);
	auto dif = tile - offset;
	if (dif.x == 0 && dif.y == 0)
		return; // Player didn't moved, no need to update anything
	offset = tile; // Offset is a tile position in the left top corner

	if (abs(dif.x) > width / 4 || abs(dif.y) > height / 4)
	{
		// If difference is too big, we simply redraw everything
		refresh();
	}
	else
	{
		// If player moved right, refresh colum on the right side of the screen
		if (dif.x > 0) refreshLocal(width - dif.x, 0, width, height);
			// And vice versa
		else refreshLocal(0, 0, -dif.x, height);

		// Same if player moved top/ bottom
		if (dif.y > 0) refreshLocal(0, height - dif.y, width, height);
		else refreshLocal(0, 0, width, -dif.y);
	}
}

// Take world position and return tile indexes

sf::Vector2i WorldRenderer::getTile(sf::Vector2f pos) const
{
	int x = static_cast<int> (pos.x / TILE_SIZE);
	int y = static_cast<int> (pos.y / TILE_SIZE);
	if (pos.x < 0) x--;
	if (pos.y < 0) y--;
	return sf::Vector2i(x, y);
}

// Draw textured quad on given position

void WorldRenderer::draw(int index, sf::FloatRect rec, sf::IntRect src, sf::Color color)
{
	// TODO: functionalize
	auto ptr = &vertices[index];
	ptr->position.x = rec.left;
	ptr->position.y = rec.top;
	ptr->texCoords.x = src.left;
	ptr->texCoords.y = src.top;
	ptr->color = color;
	ptr++;

	ptr->position.x = rec.left + rec.width;
	ptr->position.y = rec.top;
	ptr->texCoords.x = src.left + src.width;
	ptr->texCoords.y = src.top;
	ptr->color = color;
	ptr++;

	ptr->position.x = rec.left + rec.width;
	ptr->position.y = rec.top + rec.height;
	ptr->texCoords.x = src.left + src.width;
	ptr->texCoords.y = src.top + src.height;
	ptr->color = color;
	ptr++;

	ptr->position.x = rec.left;
	ptr->position.y = rec.top + rec.height;
	ptr->texCoords.x = src.left;
	ptr->texCoords.y = src.top + src.height;
	ptr->color = color;
}

// Redraw quads that belong to given tile

bool WorldRenderer::isVisible(int x, int y)
{
	return x < offset.x || x >= offset.x + width || y < offset.y || y >= offset.y + height;
}

sf::Vector2u WorldRenderer::getTile(Block block) const
{
	return sf::Vector2u((int) block % NUM_TILES.x,
						(int) block / NUM_TILES.x);
}

void WorldRenderer::refresh(int x, int y)
{
	if (isVisible(x, y))
		return;

	// Vertices works like 2d ring buffer
	auto vx = x % width;
	auto vy = y % height;
	if (vx < 0) vx += width;
	if (vy < 0) vy += height;
	// We can do this, because some tiles are never to be seen at once

	auto index = (vx + vy * width) * 4 * LAYERS;
	auto rec = sf::FloatRect(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	for (int i = 0; i < LAYERS; i++)
	{
		sf::Color color(255, 255, 255, 255);
		sf::Vector2u tile = getTile(WORLD.blocks[World::FG][x][y]);
		sf::IntRect src(tile.x*TILE_SIZE, tile.y*TILE_SIZE, TILE_SIZE, TILE_SIZE);

		// Provider(x, y, i, color, src);
		// Get color and texture rectangle from our providing function

		draw(index, rec, src, color);
		// Insert quad in vertex array
		index += 4;
	}
}

// Draw map on screen

void WorldRenderer::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
	states.texture = &TEXTURE;
	rt.draw(&vertices[0], vertices.size(), sf::PrimitiveType::Quads, states);
}

// Update screen size and position of camera

void WorldRenderer::update(sf::RenderTarget &rt)
{
	auto view = rt.getView();
	setSize(view.getSize());
	setCorner(rt.mapPixelToCoords(sf::Vector2i()));
}

void WorldRenderer::update(sf::View &view)
{
	view.setCenter(WORLD.camPos);
	setCorner(WORLD.camPos);
}