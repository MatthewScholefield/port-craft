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

#include <array>

#include "Mob.hpp"

#include "Backend/Vector.hpp"

class MobGraphics
{
public:
	static const Vector2u getSize(MobType type);
	static const Vector2u getStartPos(MobType type);
	static const int getNumAnimFrames(MobType type);
	
private:
	static const std::array<Vector2u, (int)MobType::LENGTH> SIZE, START_POS;
	static const std::array<int, (int)MobType::LENGTH> NUM_ANIM_FRAMES;
};
