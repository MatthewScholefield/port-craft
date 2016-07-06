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

#include <random>
#include "../World.hpp"
#include "WorldGenerator.hpp"
#include "SimplexNoise.hpp"
#include "State.hpp"

void WorldGenerator::generate(World &world)
{
	const float AIR_VAL = 0.f;
	const int NUM_DIRT_LAYERS = 7, RANGE = 50;
	int numDirt = 0; //0 == AIR
	float frequency = 25.0f / (float) world.WIDTH;
	State *state = State::air;
	for (int x = 0; x < world.WIDTH; ++x)
		for (int y = 0; y < world.HEIGHT; ++y)
		{
			float noise = SimplexNoise::noise((float) x*frequency, (float) y * frequency);
			float oNoise = SimplexNoise::noise((float) x*frequency / 6.f, (float) y * frequency / 6.f);
			float oNoise2 = SimplexNoise::noise((float) x*frequency / 18.f, (float) y * frequency / 18.f);
			// [-1, 1]
			
			float progress = (y - (float)world.HEIGHT / 2.f) / RANGE;
			if (progress < -1.f)
				progress = -1.f;
			else if (progress > 1.f)
				progress = 1.f;
			State *newState = state->update((3.f*oNoise2 + 2.f * oNoise + noise)/6.f, -progress);
			if (newState != state)
			{
				state = newState;
				state->enter();
			}
			world.blocks[World::FG][x][y] = state->getBlock();
		}
}