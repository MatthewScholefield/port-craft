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

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <utility>
#include <memory>
#include <string>
#include <map>

#include "World/Elements/Block.hpp"

class SoundManager;

class SoundType
{
	friend SoundManager;
public:
	SoundType();
	SoundType(int id);
	SoundType &operator=(int val);
	bool operator<(const SoundType other) const;
	const std::string &getNameCaps();
	float getVolume();

	enum
	{
		STEP = 0,
		DESTROY = 1,
		PLACE = 1,

		LENGTH
	};

private:
	int val;

	static std::array<std::string, LENGTH> namesCaps;
};

class SoundAudio
{
	friend SoundManager;
public:
	SoundAudio();
	SoundAudio(int id);
	SoundAudio(Block block);
	SoundAudio &operator=(int val);
	bool operator<(const SoundAudio other) const;
	const std::string &getNameCaps();
	bool exists();

	enum
	{
		WOOD,
		STONE,
		SNOW,
		SAND,
		LADDER,
		GRAVEL,
		GRASS,
		CLOTH,

		LENGTH
	};

private:
	int val;

	static std::array<std::string, LENGTH> namesCaps;
	
	int fromBlock(Block block);
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	bool loudSounds();
	void play();
	void pause();
	void playSfx(Block block, SoundType type);
private:
	static constexpr const char *MUSIC_NAME = "music.ogg";
	static constexpr const char *FOLDER = "audio/", *SFX_EXT = ".wav";
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Sound currentSfx;

	static constexpr int NUM_ALT_SOUNDS = 2;
	std::map< std::pair< SoundType, SoundAudio >, std::array<sf::SoundBuffer, NUM_ALT_SOUNDS>> sfxs;
	
	void playSfxInternal(SoundType type, SoundAudio audio);
};
