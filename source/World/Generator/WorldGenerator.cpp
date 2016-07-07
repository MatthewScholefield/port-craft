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
	const int RANGE = 50;
	float frequency = 25.0f / (float) world.WIDTH;
	for (int x = 0; x < world.WIDTH; ++x)
	{
		State *state = State::air;
		
		float biomeNoise = SimplexNoise::noise((float) x * frequency / 3.f);
		biomeNoise = 0.5 * biomeNoise + 0.5f;
		Biome biome = biomeChooser.choose(biomeNoise * biomeChooser.getSum());
		for (int y = 0; y < world.HEIGHT; ++y)
		{
			float smallNoise = SimplexNoise::noise((float) x*frequency, (float) y * frequency);
			float medNoise = SimplexNoise::noise((float) x * frequency / 6.f, (float) y * frequency / 6.f);
			float bigNoise = SimplexNoise::noise((float) x * frequency / 18.f, (float) y * frequency / 18.f);
			
			float threshold = (y - (float) world.HEIGHT / 2.f) / RANGE;
			if (threshold < -1.f)
				threshold = -1.f;
			else if (threshold > 1.f)
				threshold = 1.f;
			
			float noiseSum = (3.f * bigNoise + 2.f * medNoise + smallNoise) / 6.f;
			State *newState = state->update(noiseSum, -threshold, biome);
			if (newState != state)
			{
				state = newState;
				state->enter();
			}
			world.blocks[World::FG][x][y] = state->getBlock();
		}
	}
}