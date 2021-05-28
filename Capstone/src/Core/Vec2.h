#pragma once
#include <cmath>
template <class T>
class Vec2
{
public:
	//TODO: overload operators
	//TODO: vector maths
	Vec2() :x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2<T> operator+(Vec2<T>&);
	Vec2<T> operator-(Vec2<T>&);
	Vec2<T>& operator=(const Vec2<T>&);
	Vec2<T>& operator+=(Vec2<T>&);
	Vec2<T>& operator-=(Vec2<T>&);
	Vec2<T> operator*(float);
	Vec2<T>& operator/=(float);
	void set(T x, T y);
	float length();
	Vec2<T>& normalize();

	T x, y;
};

template<class T>
inline Vec2<T> Vec2<T>::operator+(Vec2<T>& other)
{
	return Vec2<T>(x + other.x, y + other.y);
}

template<class T>
inline Vec2<T> Vec2<T>::operator-(Vec2<T>& other)
{
	return Vec2<T>(x - other.x, y - other.y);
}

template<class T>
inline Vec2<T>& Vec2<T>::operator=(const Vec2<T>& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

template<class T>
inline Vec2<T>& Vec2<T>::operator+=(Vec2<T>& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<class T>
inline Vec2<T>& Vec2<T>::operator-=(Vec2<T>& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<class T>
inline void Vec2<T>::set(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<class T>
inline Vec2<T>& Vec2<T>::operator/=(float f)
{
	x /= f;
	y /= f;
	return *this;
}

template<class T>
inline float Vec2<T>::length()
{
	return std::sqrt(x * x + y * y);
}

template<class T>
inline Vec2<T>& Vec2<T>::normalize()
{
	if (length() == 0)
		return *this;
	*this /= length();
	return *this;
}

template<class T>
inline Vec2<T> Vec2<T>::operator*(float f)
{
	return Vec2(x * f, y * f);
}