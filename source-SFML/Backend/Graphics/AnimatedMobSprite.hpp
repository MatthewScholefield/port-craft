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
#include "RenderWindow.hpp"
#include "World/Entities/Mobs/MobSpriteState.hpp"
#include "AnimatedSpritePlayer.hpp"
#include "../Vector.hpp"

class MobSpriteData;
class Animation;
namespace sf
{
class Time;
class Texture;
class RenderWindow;
}

class AnimatedMobSprite
{
public:
	AnimatedMobSprite(const MobSpriteData &data, const sf::Texture &texture);
	
	void setPaused(bool isPaused);
	void setPosition(float x, float y);
	void setPosition(Vector2f pos);
	void setFlipped(bool flipped);
	void update(sf::Time dt);
	void draw(MobSpriteState state, RenderWindow &window);
	
private:
	MobSpriteState prevState;
	std::array<Animation, (int)MobSpriteState::LENGTH> animations;
	AnimatedSpritePlayer spritePlayer;
};
