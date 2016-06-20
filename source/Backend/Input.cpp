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


#include <iostream>

#include <SFML/Window.hpp>

#include "Input.hpp"

sf::Keyboard::Key getSFMLKey(Keys k)
{
	if (k==Keys::Left)
		return sf::Keyboard::Left;
	else if (k==Keys::Right)
		return sf::Keyboard::Right;
	else if (k==Keys::Up)
		return sf::Keyboard::Up;
	else if (k==Keys::Down)
		return sf::Keyboard::Down;

	return sf::Keyboard::Unknown;
}

bool isKeyPressed(Keys k)
{
	return sf::Keyboard::isKeyPressed(getSFMLKey(k));
}
