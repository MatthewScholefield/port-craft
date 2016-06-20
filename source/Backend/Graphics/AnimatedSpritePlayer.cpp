////////////////////////////////////////////////////////////
//
// Copyright (C) 2014 Maximilian Wagenbach (aka. Foaly) (foaly.f@web.de)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
// you must not claim that you wrote the original software.
// If you use this software in a product, an acknowledgment
// in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
// and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

// Notice: Changed formatting, renamed variables, changed NULL -> nullptr,
// and renamed class from AnimatedSprite to AnimatedSpritePlayer
#include <iostream>

#include "AnimatedSpritePlayer.hpp"

AnimatedSpritePlayer::AnimatedSpritePlayer(sf::Time frameTime, bool paused, bool looped) :
animation(nullptr), frameTime(frameTime), frameNum(0),
paused(paused), looped(looped), texture(nullptr) { }

void AnimatedSpritePlayer::setAnimation(const Animation &animation)
{
	this->animation = &animation;
	texture = this->animation->getSpriteSheet();
	frameNum = 0;
	setFrame(frameNum);
}

void AnimatedSpritePlayer::setFrameTime(sf::Time time)
{
	frameTime = time;
}

void AnimatedSpritePlayer::play()
{
	paused = false;
}

void AnimatedSpritePlayer::play(const Animation& animation)
{
	if (getAnimation() != &animation)
		setAnimation(animation);
	play();
}

void AnimatedSpritePlayer::pause()
{
	paused = true;
}

void AnimatedSpritePlayer::stop()
{
	paused = true;
	frameNum = 0;
	setFrame(frameNum);
}

void AnimatedSpritePlayer::setLooped(bool looped)
{
	looped = looped;
}

void AnimatedSpritePlayer::setColor(const sf::Color& color)
{
	// Update the vertices' color
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;
}

const Animation* AnimatedSpritePlayer::getAnimation() const
{
	return animation;
}

sf::FloatRect AnimatedSpritePlayer::getLocalBounds() const
{
	sf::IntRect rect = animation->getFrame(frameNum);

	float width = static_cast<float> (std::abs(rect.width));
	float height = static_cast<float> (std::abs(rect.height));

	return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSpritePlayer::getGlobalBounds() const
{
	return getTransform().transformRect(getLocalBounds());
}

bool AnimatedSpritePlayer::isLooped() const
{
	return looped;
}

bool AnimatedSpritePlayer::isPlaying() const
{
	return !paused;
}

sf::Time AnimatedSpritePlayer::getFrameTime() const
{
	return frameTime;
}

void AnimatedSpritePlayer::setFrame(std::size_t newFrame, bool resetTime)
{
	if (animation)
	{
		//calculate new vertex positions and texture coordiantes
		sf::IntRect rect = animation->getFrame(newFrame);

		vertices[0].position = sf::Vector2f(0.f, 0.f);
		vertices[1].position = sf::Vector2f(0.f, static_cast<float> (rect.height));
		vertices[2].position = sf::Vector2f(static_cast<float> (rect.width), static_cast<float> (rect.height));
		vertices[3].position = sf::Vector2f(static_cast<float> (rect.width), 0.f);

		float left = static_cast<float> (rect.left) + 0.0001f;
		float right = left + static_cast<float> (rect.width);
		float top = static_cast<float> (rect.top);
		float bottom = top + static_cast<float> (rect.height);

		vertices[0].texCoords = sf::Vector2f(left, top);
		vertices[1].texCoords = sf::Vector2f(left, bottom);
		vertices[2].texCoords = sf::Vector2f(right, bottom);
		vertices[3].texCoords = sf::Vector2f(right, top);
	}

	if (resetTime)
		currentTime = sf::Time::Zero;
}

void AnimatedSpritePlayer::update(sf::Time deltaTime)
{
	// if not paused and we have a valid animation
	if (!paused && animation)
	{
		// add delta time
		currentTime += deltaTime;
		std::cout << "Here " << currentTime.asSeconds() << std::endl;
		std::cout << "dt:" << deltaTime.asSeconds() << " frame:" << frameTime.asSeconds() << std::endl;

		// if current time is bigger then the frame time advance one frame
		if (currentTime >= frameTime)
		{
			currentTime -= frameTime;
			// reset time, but keep the remainder
			//currentTime = sf::microseconds(currentTime.asMicroseconds() % frameTime.asMicroseconds());

			// get next Frame index
			if (frameNum + 1 < animation->getSize())
				frameNum++;
			else
			{
				// animation has ended
				frameNum = 0; // reset to start

				if (!looped)
				{
					paused = true;
				}

			}

			// set the current frame, not reseting the time
			setFrame(frameNum, false);
		}
	}
}

void AnimatedSpritePlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (animation && texture)
	{
		states.transform *= getTransform();
		states.texture = texture;
		target.draw(vertices, 4, sf::Quads, states);
	}
}