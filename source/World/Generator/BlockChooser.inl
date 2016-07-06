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

template<typename K, typename... Ts>
const int NumChooser<K, Ts...>::getSum()
{
	return SUM;
}

template<typename K, typename... Ts>
template<typename T, typename... Args>
constexpr int NumChooser<K, Ts...>::adder()
{
	return T::PROB + adder < Args...>();
}

template<typename K, typename... Ts>
template <typename... Args, typename>
constexpr int NumChooser<K, Ts...>::adder()
{
	return 0;
}

template<typename K, typename... Ts>
NumChooser<K, Ts...>::NumChooser() : SUM(adder < Ts... >()) { }

template<typename K, typename... Ts>
template<typename T, typename... Args>
constexpr K NumChooser<K, Ts...>::find(int left, K block)
{
	return left < 0 ? block : find < Args... >(left - T::PROB, T::NUM);
}

template<typename K, typename... Ts>
template <typename... Args, typename>
constexpr K NumChooser<K, Ts...>::find(int left, K block)
{
	return block;
}

template<typename K, typename... Ts>
constexpr K NumChooser<K, Ts...>::choose(int randVal)
{
	return find < Ts... >(randVal);
}

template<typename K, typename... Ts>
constexpr K NumChooser<K, Ts...>::choose()
{
	return choose(rand() % SUM);
}