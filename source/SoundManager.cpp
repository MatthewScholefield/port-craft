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
	"STEP",
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

SoundAudio::SoundAudio(Block block) : val(fromBlock(block)) { }

SoundAudio &SoundAudio::operator=(int val)
{
	this->val = val;
	return *this;
}

int SoundAudio::fromBlock(Block block)
{
	switch((int)block)
	{
	case Block::SAND:
		return SAND;
		
	case Block::GRASS_SNOW:
		return SNOW;
		
	case Block::GRAVEL:
		return GRAVEL;
		
	case Block::WOOL_BLACK:
	case Block::WOOL_RED:
	case Block::WOOL_GREEN_DARK:
	case Block::WOOL_GREEN_LIGHT:
	case Block::WOOL_BROWN:
	case Block::WOOL_BLUE_DARK:
	case Block::WOOL_PURPLE:
	case Block::WOOL_CYAN:
	case Block::WOOL_GRAY_DARK:
	case Block::WOOL_GRAY_LIGHT:
	case Block::WOOL_WHITE:
	case Block::WOOL_PINK:
	case Block::WOOL_YELLOW:
	case Block::WOOL_BLUE_LIGHT:
	case Block::WOOL_MAGENTA:
	case Block::WOOL_ORANGE:
		return CLOTH;
		
	case Block::LEAVES_JUNGLE:
	case Block::LEAVES_OAK:
	case Block::LEAVES_SPRUCE:
	case Block::SAPLING_JUNGLE:
	case Block::SAPLING_OAK:
	case Block::SAPLING_SPRUCE:
		return GRASS;
		
	case Block::LOG_OAK:
	case Block::LOG_JUNGLE:
	case Block::LOG_BIRCH:
	case Block::LOG_SPRUCE:
	case Block::PLANKS_WOOD:
	case Block::CHEST:
	case Block::LADDER:
		return WOOD;
	
	case Block::GRASS_JUNGLE:
	case Block::GRASS:
	case Block::DIRT:
	case Block::MYCELIUM:
		return GRASS;
	
	case Block::STONE:
	case Block::SANDSTONE:
	case Block::COBBLESTONE:
	case Block::ORE_COAL:
	case Block::ORE_IRON:
	case Block::ORE_GOLD:
	case Block::ORE_DIAMOND:
	case Block::BEDROCK:
		return STONE;
	}
	return -1;
}

bool SoundAudio::operator<(const SoundAudio other) const
{
	return val < other.val;
}

bool SoundAudio::exists()
{
	return val >= 0;
}

SoundManager::SoundManager() { }

SoundManager::~SoundManager() { }

void SoundManager::playSfx(Block block, SoundType type)
{
	SoundAudio audio(block);
	if (audio.exists())
		playSfxInternal(type, audio);
}

void SoundManager::playSfxInternal(SoundType type, SoundAudio audio)
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
