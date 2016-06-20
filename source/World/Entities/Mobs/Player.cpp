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

#include "Player.hpp"

#include "Backend/Vector.hpp"
#include "Backend/Input.hpp"

MobSpriteData Player::spriteData(Vector2u(0, 0), Vector2u(16, 32));

Player::Player(const Vector2f &pos) : Mob(MobType::PLAYER, spriteData, pos) { }

const MobSpriteData& Player::getSpriteData()
{
	return spriteData;
}

void Player::updateMob(float dt, World& world)
{
	float WALK_SPEED = 100.f;
	
	vel.x = 0;
	if (isKeyPressed(Keys::Left))
		vel.x = -WALK_SPEED;
	if (isKeyPressed(Keys::Right))
		vel.x = +WALK_SPEED;
	if (isKeyPressed(Keys::Up))
		vel.y = -WALK_SPEED;
	if (isKeyPressed(Keys::Down) && vel.y < WALK_SPEED)
		vel.y = +WALK_SPEED;
}
