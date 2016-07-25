#include "WorldRenderer.hpp"
#include "../Backend/types.hpp"
#include "Backend/Graphics/RenderWindow.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cassert>
#include <iostream>

WorldRenderer::WorldRenderer(World &world, const sf::Texture &TEXTURE, unsigned int tileSize, int layers)
: world(world), TEXTURE(TEXTURE), TILE_SIZE(tileSize), LAYERS(layers), NUM_TILES(TEXTURE.getSize() / tileSize)
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
		const float MAX_BRIGHTNESS = 255.f;
		float mag = world.brightness[x][y] * MAX_BRIGHTNESS;
		Block block = world.blocks[World::FG][x][y];
		if (block == Block::AIR)
		{
			block = world.blocks[World::BG][x][y];
			mag *= 0.6f;
		}
		sf::Color color(mag, mag, mag);
		sf::Vector2u tile = getTile(block);
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
	view.setCenter(world.camPos * (float)World::BLOCK_PX);
}

const int WorldRenderer::SUB_AMOUNT[16] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3};

void WorldRenderer::brightnessUpdate(int x, int y, float brightness)
{
	if ((unsigned) x >= World::WIDTH || (unsigned) y >= World::HEIGHT)
		return;
	float before = world.brightness[x][y];
	float after = std::max(before, brightness);
	const float MIN_DIFF = 1.f/256.f/2.f;
	if (std::abs(before - after) > MIN_DIFF)
	{
		world.brightness[x][y] = after;
		float mult = world.blocks[World::FG][x][y].isWalkThrough() ? 0.88f : 0.7f;
		float give = after * mult;
		brightnessUpdate(x + 1, y, give);
		brightnessUpdate(x - 1, y, give);
		brightnessUpdate(x, y + 1, give);
		brightnessUpdate(x, y - 1, give);
	}
}

void WorldRenderer::checkBlock(int x, int y)
{
	float mult = world.blocks[World::FG][x][y].isWalkThrough() ? 0.88f : 0.7f;
	float brightness = world.brightness[x][y] * mult;
	brightnessUpdate(x + 1, y, brightness);
	brightnessUpdate(x - 1, y, brightness);
	brightnessUpdate(x, y + 1, brightness);
	brightnessUpdate(x, y - 1, brightness);
}

void WorldRenderer::calculateBrightness(int leftBound, int rightBound, int topBound, int bottomBound)
{
	const int PADDING = MAX_BRIGHTNESS_SPREAD + UPDATE_LEN;
	const int MIN_X = std::max(leftBound - PADDING, 0);
	const int MAX_X  = std::min(rightBound + PADDING, world.WIDTH - 1);
	const int MIN_Y = std::max(topBound - PADDING, 0);
	const int MAX_Y = std::min(bottomBound + PADDING, world.HEIGHT - 1);

	for (int x = MIN_X; x <= MAX_X; ++x)
	{
		bool sunLit = true;
		for (int y = 0; y <= MAX_Y; ++y)
		{
			Block block = world.blocks[World::FG][x][y];
			if (y >= MIN_Y)
				world.brightness[x][y] = sunLit ? 1.f : 0.f;
			if (sunLit)
				if (!block.isWalkThrough())
				{
					if (y < MIN_Y - 1)
						y = MIN_Y - 1;
					sunLit = false;
				}
		}
	}
	for (int i = MIN_X; i <= MAX_X; ++i)
		for (int j = MIN_Y; j <= MAX_Y; ++j)
			checkBlock(i, j);
}

void WorldRenderer::calculateBrightnessAround(Vector2f pos, RenderWindow &window)
{
	const Vector2f &SIZE = window.getSizeUnits() / 2.f;
	int left = pos.x - SIZE.x;
	int right = pos.x + SIZE.x;
	int top = pos.y - SIZE.y;
	int bottom = pos.y + SIZE.y;
	
	calculateBrightness(left, right, top, bottom);
}

void WorldRenderer::calculateAllBrightness()
{
	calculateBrightness(0, WORLD_WIDTH - 1, 0, WORLD_HEIGHT - 1);
}