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

#include "../Entity.hpp"

#include "Backend/Vector.hpp"
#include "MobSpriteData.hpp"
#include "Backend/Graphics/RenderWindow.hpp"
#include "Backend/Graphics/AnimatedMobSprite.hpp"
#include "MobSpriteState.hpp"

class World;
namespace sf
{
class Texture;
}

enum class MobType
{
	PLAYER = 0,
	LENGTH
};

class Mob : public Entity
{
public:
	static void init();
	Mob(const MobType MOB_TYPE, const MobSpriteData &data, const Vector2f &pos);
	virtual ~Mob() = default;
	
	virtual const MobSpriteData &getSpriteData() = 0;
	void draw(RenderWindow &window) override;
	
protected:
	void updateEntity(float dt, World &world) override;
	virtual void updateMob(float dt, World &world) = 0;
	
	const MobType MOB_TYPE;
	AnimatedMobSprite sprite;
	MobSpriteState spriteState;
	
private:
	static sf::Texture texture;
};
