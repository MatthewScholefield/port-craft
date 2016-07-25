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
#include "Backend/Vector.hpp"
#include "SpriteRenderer.hpp"
#include "World/Elements/Block.hpp"
#include "RenderWindow.hpp"

SpriteRenderer::SpriteRenderer(const sf::Texture &TEXTURE) : TEXTURE(TEXTURE)
{
	sprite.setTexture(TEXTURE);
}

void SpriteRenderer::renderBlock(float x, float y, Block block, RenderWindow &renderWindow)
{
	sf::RenderWindow &window = renderWindow.getWindow();
	const int BLOCKS_PER_COL = 16;
	int ty = (int) block / BLOCKS_PER_COL;
	int tx = (int) block % BLOCKS_PER_COL;
	const Vector2f &CENTER = window.getView().getCenter();
	const Vector2f CORNER = CENTER - (Vector2f)window.getSize() / (2.f * renderWindow.getScale());
	sprite.setTextureRect(sf::IntRect(tx * 16, ty * 16, 16, 16));
	sprite.setPosition(CORNER.x + 16.f * x, CORNER.y + 16.f * y);
	printf("REndering, x:%f\n", CORNER.x + 16.f * x);
	window.draw(sprite);
}
