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
spriteState(MobSpriteState::NORMAL) { }

void Mob::draw(RenderWindow &window)
{
	Vector2f pixPos = getPixPos(window); // TODO: Change World::BLOCK_PIX * window.getScale() or something
	pixPos -= ((Vector2f) getSpriteData().getSize() - 16.f * getSize()) / 2.f;
	sprite.setPosition(pixPos);
	sprite.draw(spriteState, window);
}

void Mob::updateEntity(float dt, World &world)
{
	sprite.update(sf::seconds(dt));
	sprite.setPaused(std::abs(vel.x) < EPSILON);
	updateMob(dt, world);
	updatePhysics(dt, world);
}

void Mob::checkColPoint(bool right, int sign, Vector2f pt, World &world)
{
	if (!world.getBlock(pt).isWalkThrough())
	{
		float val;
		float depthTop = std::modf(right ? pt.x : pt.y, &val);
		if (sign == 1)
			depthTop = 1.f - depthTop;

		if (right)
			pos.x += sign * depthTop;
		else
			pos.y += sign * depthTop;

		if (right)
		{
			if (-sign * vel.x > 0)
				vel.x = 0;
		}
		else if (-sign * vel.y > 0)
			vel.y = 0;
	}
}

void Mob::updatePhysics(float dt, World &world)
{
	const Vector2f &size = (Vector2f) getSize();
	Vector2f bottomRight = (pos + size);
	Vector2f center = (bottomRight + pos) / 2.f;
	for (float x = pos.x; x < 1 + bottomRight.x; ++x)
	{
		if (x > bottomRight.x)
			x = bottomRight.x;
		for (float y = pos.y; y < 1 + bottomRight.y; ++y)
		{
			if (y > bottomRight.y)
				y = bottomRight.y;
			if (abs(x - pos.x) >= EPSILON && abs(x - bottomRight.x) >= EPSILON)
				checkColPoint(false, y > center.y ? -1 : 1, Vector2f(x, y), world);
			else if (abs(y - pos.y) >= EPSILON && abs(y - bottomRight.y) >= EPSILON)
				checkColPoint(true, x > center.x ? -1 : 1, Vector2f(x, y), world);
			else
			{
				checkColPoint(false, y > center.y ? -1 : 1, Vector2f(x, y), world);
				checkColPoint(true, x > center.x ? -1 : 1, Vector2f(x, y), world);
			}
		}
	}
	checkColPoint(false, -1, Vector2f((bottomRight.x + pos.x) / 2.f, bottomRight.y), world);

}
