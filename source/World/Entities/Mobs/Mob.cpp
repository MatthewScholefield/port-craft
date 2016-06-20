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

sf::Texture Mob::texture;

void Mob::init()
{
	sf::Image image;
	image.loadFromFile("mobs.png");
	image.createMaskFromColor(sf::Color(255,0,255),0);
	texture.loadFromImage(image);
}

Mob::Mob(const MobType MOB_TYPE, const MobSpriteData &data, const Vector2f &pos) : Entity(EntityType::MOB, pos), MOB_TYPE(MOB_TYPE),
sprite(data, texture), spriteState(MobSpriteState::NORMAL) { }

void Mob::draw(RenderWindow &window)
{
	sprite.setPosition(pos);
	sprite.draw(spriteState, window);
}

void Mob::updateEntity(float dt, World &world)
{
	sprite.update(sf::seconds(dt));
	sprite.setPaused(false);
	//sprite.setPaused(std::abs(vel.x) < EPSILON);
}
