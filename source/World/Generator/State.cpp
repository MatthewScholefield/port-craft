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

#include "State.hpp"

State *State::air = new AirState(),
*State::grass = new GrassState(),
*State::dirt = new DirtState(),
*State::stone = new StoneState();

void State::enter() { }

State *State::update(float noise)
{
	if (noise < 0)
		return air;
	else
		return updateVirtual(noise);
}

State *AirState::updateVirtual(float noise)
{
	return State::grass;
}

Block AirState::getBlock()
{
	return Block::AIR;
}

State *GrassState::updateVirtual(float noise)
{
	return State::dirt;
}

Block GrassState::getBlock()
{
	return Block::GRASS;
}

void DirtState::enter()
{
	count = 0;
}

State *DirtState::updateVirtual(float noise)
{
	if (++count >= NUM_DIRT)
		return State::stone;
	else
		return State::dirt;
}

Block DirtState::getBlock()
{
	return Block::DIRT;
}

State *StoneState::updateVirtual(float noise)
{
	return State::stone;
}

Block StoneState::getBlock()
{
	return STONES.choose();
}