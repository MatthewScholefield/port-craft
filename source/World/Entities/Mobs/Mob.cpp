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

#include <cmath>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "Mob.hpp"
#include "Entities/Entity.hpp"
#include "Graphics/AnimatedMobSprite.hpp"

#include "Backend/types.hpp"
#include "Backend/Vector.hpp"
#include "Backend/Graphics/RenderWindow.hpp"
#include "SoundManager.hpp"
#include "World.hpp"

sf::Texture Mob::texture;

void Mob::init()
{
	sf::Image image;
	image.loadFromFile("mobs.png");
	image.createMaskFromColor(sf::Color(255, 0, 255), 0);
	texture.loadFromImage(image);
}

Mob::Mob(const MobType MOB_TYPE, const MobSpriteData &data, const Vector2f &pos) :
Entity(EntityType::MOB, pos), MOB_TYPE(MOB_TYPE), sprite(data, texture),
spriteState(MobSpriteState::NORMAL), facingLeft(false), sinceLastSfx(0.f) { }

void Mob::draw(RenderWindow &window, World &world)
{
	Vector2f pixPos = (Vector2f) world.coordToPix(pos); // TODO: Change World::BLOCK_PIX * window.getScale() or something
	pixPos -= ((Vector2f) getSpriteData().getSize() - (Vector2f) world.coordToPix(getSize())) / 2.f;
	if (facingLeft)
		pixPos.x += getSpriteData().getSize().x;
	sprite.setPosition(pixPos);
	sprite.draw(spriteState, window);
}

void Mob::updateEntity(float dt, World &world)
{
	sprite.update(sf::seconds(dt));
	sprite.setPaused(std::abs(vel.x) < EPSILON);
	if (facingLeft)
	{
		if (vel.x > 0)
		{
			facingLeft = false;
			sprite.setFlipped(false);
		}
	}
	else
	{
		if (vel.x < 0)
		{
			facingLeft = true;
			sprite.setFlipped(true);
		}
	}
	updateMob(dt, world);
}

void Mob::updatePhysics(float dt, World &world)
{
	Entity::updatePhysics(dt, world);

	const Vector2f &size = (Vector2f) getSize();
	float left = pos.x;
	float top = pos.y;
	float right = left + size.x;
	float bottom = top + size.y;
	float center = (top + bottom) / 2.f;

	bool stuckBottomLeft = !world.getBlock(left, bottom).isWalkThrough();
	bool stuckBottomRight = !world.getBlock(right, bottom).isWalkThrough();
	bool stuckCenterLeft = !world.getBlock(left, center).isWalkThrough();
	bool stuckCenterRight = !world.getBlock(right, center).isWalkThrough();
	bool stuckTopLeft = !world.getBlock(left, top).isWalkThrough();
	bool stuckTopRight = !world.getBlock(right, top).isWalkThrough();

	float inRight = right - (int) right;
	float inLeft = 1.0 - (left - (int) left);

	float inBottom = bottom - (int) bottom;
	float inTop = 1.0 - (top - (int) top);


	if (stuckCenterLeft)
	{
		pos.x += inLeft;
		vel.x = 0;
		inLeft = 0;
	}
	else if (stuckCenterRight)
	{
		pos.x -= inRight;
		vel.x = 0;
		inRight = 0;
	}

	if (stuckBottomLeft && stuckBottomRight)
	{
		pos.y -= inBottom;
		vel.y = 0;
	}
	else if (stuckBottomLeft)
	{
		if (inBottom < inLeft && !stuckTopLeft)
		{
			pos.y -= inBottom;
			vel.y = 0;
		}
		else
		{
			pos.x += inLeft;
			vel.x = 0;
		}
	}
	else if (stuckBottomRight)
	{
		if (inBottom < inRight && !stuckTopRight)
		{
			pos.y -= inBottom;
			vel.y = 0;
		}
		else
		{
			pos.x -= inRight;
			vel.x = 0;
		}
	}

	if (stuckTopLeft && stuckTopRight)
	{
		pos.y += inTop;
		vel.y = 0;
	}
	else if (stuckTopLeft)
	{
		if (inTop < inLeft && !stuckBottomLeft)
		{
			pos.y += inTop;
			vel.y = 0;
		}
		else
		{
			pos.x += inLeft;
			vel.x = 0;
		}
	}
	else if (stuckTopRight)
	{
		if (inTop < inRight && !stuckBottomRight)
		{
			pos.y += inTop;
			vel.y = 0;
		}
		else
		{
			pos.x -= inRight;
			vel.x = 0;
		}
	}
}

void Mob::updateSound(float dt, SoundManager &manager, World &world)
{
	if (abs(vel.x) > EPSILON)
	{
		sinceLastSfx += dt;
		if (sinceLastSfx > STEP_SFX_TIME)
		{
			sinceLastSfx -= STEP_SFX_TIME;
			const Vector2f &size = (Vector2f) getSize();
			Block block = world.getBlock(pos.x + size.x/2, pos.y + size.y);
			printf("Playing %d\n", (int)block);
			manager.playSfx(block, SoundType::STEP);
		}
	}
	else
		sinceLastSfx = STEP_SFX_TIME;
}
