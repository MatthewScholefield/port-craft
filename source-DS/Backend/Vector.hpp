#pragma once
template <typename T>
class Vector2
{
public:
	//-- Variables --
	T x;
	T y;
	
	//-- Functions --
	
	// Default constructor
	Vector2();
	
	// Parameter constructor
	Vector2(T x,T y);
	
	
	//-- Operators --
	
	Vector2<T> operator-();
	Vector2<T>& operator+=(const Vector2<T>& right);
	Vector2<T>& operator-=(const Vector2<T>& right);
	Vector2<T> operator+(const Vector2<T>& right) const;
	Vector2<T> operator-(const Vector2<T>& right) const;
	Vector2<T> operator*(T scalar) const;
	Vector2<T> operator/(T scalar) const;
	Vector2<T>& operator*=(T scalar);
	Vector2<T>& operator/=(T scalar);
	
	bool operator==(const Vector2<T>& right) const;
	bool operator!=(const Vector2<T>& right) const;
	
};

#include "Backend/Vector.inl"

typedef Vector2<int>          Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float>        Vector2f;
