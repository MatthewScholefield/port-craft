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
#include "TextureManager.hpp"

TextureManager::TextureManager() { }

TextureManager::TextureManager(const TextureManager& orig) { }

TextureManager::~TextureManager() { }

bool TextureManager::loadTexture()
{
	if (!image.loadFromFile("texture.png"))
		return false;
	image.createMaskFromColor(sf::Color(255, 0, 255));
	texture.loadFromImage(image);
	texture.setSmooth(false);
	return true;
}

sf::Texture &TextureManager::getTexture()
{
	return texture;
}