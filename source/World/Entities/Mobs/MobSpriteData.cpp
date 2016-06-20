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

#include "MobSpriteData.hpp"

MobSpriteData::MobSpriteData(const Vector2u &START_POS, const Vector2u &SIZE,
							 const int NUM_FRAMES) :
SIZE(SIZE), START_POS(START_POS), NUM_FRAMES(NUM_FRAMES) { }

const Vector2u &MobSpriteData::getSize() const
{
	return SIZE;
}

const Vector2u &MobSpriteData::getStartPos() const
{
	return START_POS;
}

const int MobSpriteData::getNumFrames() const
{
	return NUM_FRAMES;
}
