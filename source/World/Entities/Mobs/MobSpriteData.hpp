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

#include "Backend/Vector.hpp"

class MobSpriteData
{
public:
	MobSpriteData(const Vector2u &START_POS, const Vector2u &SIZE,
				 const int NUM_SPRITE_FRAMES = 6);
	
	const Vector2u &getSize() const;
	const Vector2u &getStartPos() const;
	const int getNumFrames() const;
	
private:
	const Vector2u SIZE, START_POS;
	const int NUM_FRAMES;
};
