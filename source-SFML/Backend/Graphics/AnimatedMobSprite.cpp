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

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "AnimatedMobSprite.hpp"
#include "Animation.hpp"

#include "World/Entities/Mobs/MobSpriteData.hpp"
#include "World/Entities/Mobs/MobSpriteState.hpp"

AnimatedMobSprite::AnimatedMobSprite(const MobSpriteData &data, const sf::Texture &texture) :
prevState((MobSpriteState)-1), animations({}), spritePlayer()
{
	for (int id = 0; id < animations.size(); ++id)
	{
		animations[id].setSpriteSheet(texture);
		
		const Vector2i START_POS((Vector2i)data.getStartPos() + Vector2i(0, data.getSize().y * id));
		const int END = START_POS.x + data.getNumFrames() * data.getSize().x;

		for (Vector2i pos = START_POS; pos.x < END; pos.x += data.getSize().x)
			animations[id].addFrame(sf::IntRect(pos, (Vector2i)data.getSize()));
	}
}

void AnimatedMobSprite::setPaused(bool setPaused)
{
	if (setPaused)
		spritePlayer.pause();
	else
		spritePlayer.play();
}

void AnimatedMobSprite::setPosition(float x, float y)
{
	spritePlayer.setPosition(x, y);
}

void AnimatedMobSprite::setPosition(Vector2f pos)
{
	spritePlayer.setPosition(pos);
}

void AnimatedMobSprite::update(sf::Time dt)
{
	spritePlayer.update(dt);
}

void AnimatedMobSprite::draw(MobSpriteState state, RenderWindow &window)
{
	if (prevState != state)
	{
		spritePlayer.setAnimation(animations[(int)state]);
		prevState = state;
	}
	window.draw(spritePlayer);
}
