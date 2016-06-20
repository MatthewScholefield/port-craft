#include "Vector.hpp"

template <typename T>
Vector2<T>::Vector2() : x(0), y(0) {}

template <typename T>
Vector2<T>::Vector2(T x,T y) : x(x), y(y) {}

template <typename T>
Vector2<T> Vector2<T>::operator-()
{
	Vector2<T> tmp(-x,-y);	
	return tmp;
}

template <typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& right)
{
	x += right.x;
	y += right.y;
	
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& right)
{
	x -= right.x;
	y -= right.y;
	
	return *this;
}

template <typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& right) const
{
	return Vector2<T>(x+right.x,y+right.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& right) const
{
	return Vector2<T>(x-right.x,y-right.y);
}

template <typename T>
Vector2<T> Vector2<T>::operator*(T scalar) const
{
	return Vector2<T>(x*scalar,y*scalar);
}

template <typename T>
Vector2<T> Vector2<T>::operator/(T scalar) const
{
	return Vector2<T>(x/scalar,y/scalar);
}

template <typename T>
Vector2<T>& Vector2<T>::operator*=(T scalar)
{
	x *= scalar;
	y *= scalar;
	
	return *this;
}

template <typename T>
Vector2<T>& Vector2<T>::operator/=(T scalar)
{
	x /= scalar;
	y /= scalar;
	
	return *this;
}

template <typename T>
bool Vector2<T>::operator==(const Vector2<T>& right) const
{
	return x == right.x && y == right.y;
}

template <typename T>
bool Vector2<T>::operator!=(const Vector2<T>& right) const
{
	return !operator==(right);
}
