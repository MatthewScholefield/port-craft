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

#include <random>

template<typename... Ts>
const int BlockChooser<Ts...>::getSum()
{
	return SUM;
}

template<typename... Ts>
template<typename T, typename... Args>
constexpr int BlockChooser<Ts...>::adder()
{
	return T::PROB + adder < Args...>();
}

template<typename... Ts>
template <typename... Args, typename>
constexpr int BlockChooser<Ts...>::adder()
{
	return 0;
}

template<typename... Ts>
BlockChooser<Ts...>::BlockChooser() : SUM(adder < Ts... >()) { }

template<typename... Ts>
template<typename T, typename... Args>
constexpr Block BlockChooser<Ts...>::find(int left, Block block)
{
	return left < 0 ? block : find < Args... >(left - T::PROB, T::BLOCK);
}

template<typename... Ts>
template <typename... Args, typename>
constexpr Block BlockChooser<Ts...>::find(int left, Block block)
{
	return block;
}

template<typename... Ts>
constexpr Block BlockChooser<Ts...>::choose(int randVal)
{
	return find < Ts... >(randVal);
}

template<typename... Ts>
constexpr Block BlockChooser<Ts...>::choose()
{
	return choose(rand() % SUM);
}