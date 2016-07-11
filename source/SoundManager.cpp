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

#include <SFML/Audio/SoundBuffer.hpp>

#include "SoundManager.hpp"

std::array<std::string, SoundType::LENGTH> SoundType::namesCaps = {
	"PLACE",
	"DIG"
};

std::array<std::string, SoundAudio::LENGTH> SoundAudio::namesCaps = {
	"WOOD",
	"STONE",
	"SNOW",
	"SAND",
	"LADDER",
	"GRAVEL",
	"GRASS",
	"CLOTH",
};

const std::string &SoundType::getNameCaps()
{
	return namesCaps[val];
}

const std::string &SoundAudio::getNameCaps()
{
	return namesCaps[val];
}

SoundType::SoundType() { }

SoundType::SoundType(int id) : val(id) { }

SoundType &SoundType::operator=(int val)
{
	this->val = val;
	return *this;
}

bool SoundType::operator<(const SoundType other) const
{
	return val < other.val;
}

SoundAudio::SoundAudio() { }

SoundAudio::SoundAudio(int id) : val(id) { }

SoundAudio &SoundAudio::operator=(int val)
{
	this->val = val;
	return *this;
}

bool SoundAudio::operator<(const SoundAudio other) const
{
	return val < other.val;
}

SoundManager::SoundManager() { }

SoundManager::~SoundManager() { }

void SoundManager::playSfx(SoundType type, SoundAudio audio)
{
	std::pair<SoundType, SoundAudio> key = std::make_pair(type, audio);
	std::array<sf::SoundBuffer, NUM_ALT_SOUNDS> &buffers = sfxs[key];
	sf::SoundBuffer &buffer = buffers[rand() % NUM_ALT_SOUNDS];
	currentSfx.setBuffer(buffer);
	currentSfx.play();
}

bool SoundManager::loudSounds()
{
	if (!buffer.loadFromFile(MUSIC_NAME))
		return false;
	sound.setBuffer(buffer);
	sound.setLoop(true);

	for (int type = 0; type < SoundType::LENGTH; ++type)
	{
		for (int audio = 0; audio < SoundAudio::LENGTH; ++audio)
		{
			SoundType soundType = type;
			SoundAudio soundAudio = audio;

			std::string baseFileName = FOLDER + soundType.getNameCaps() + '_' +
					soundAudio.getNameCaps();

			std::array<sf::SoundBuffer, NUM_ALT_SOUNDS> buffers = {};
			for (int alt = 1; alt <= NUM_ALT_SOUNDS; ++alt)
			{
				std::string fileName = baseFileName + '_' + std::to_string(alt) + SFX_EXT;
				sf::SoundBuffer &buffer = buffers[alt - 1];
				buffer.loadFromFile(fileName.c_str());
			}
			auto key = std::make_pair(soundType, soundAudio);
			sfxs[key] = buffers;
		}
	}

	return true;
}

void SoundManager::play()
{
	sound.play();
}

void SoundManager::pause()
{
	sound.pause();
}
