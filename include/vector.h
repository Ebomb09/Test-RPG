#ifndef GAME_VECTOR_H
#define GAME_VECTOR_H

#include <cmath>

template <class T>
struct tuple_2{

	T x = 0; 
	T y = 0;

	tuple_2<T> operator+(const tuple_2<T>& add){
		return tuple_2<T>{x + add.x, y + add.y};
	}

	tuple_2<T>& operator+=(const tuple_2<T>& add){
		x += add.x;
		y += add.y;
		return *this;
	}

	tuple_2<T> operator-(const tuple_2<T>& sub){
		return tuple_2<T>{x - sub.x, y - sub.y};
	}

	tuple_2<T>& operator-=(const tuple_2<T>& sub){
		x -= sub.x;
		y -= sub.y;
		return *this;
	}

	template <class Tn>
	tuple_2<T> operator*(const Tn& mult){
		return tuple_2<T>{static_cast<T>(x * mult), static_cast<T>(y * mult)};
	}

	template <class Tn>
	tuple_2<T>& operator*=(const Tn& mult){
		x = static_cast<T>(x * mult);
		y = static_cast<T>(y * mult);
		return *this;
	}

	template <class Tn>
	tuple_2<T> operator/(const Tn& div){
		return tuple_2<T>{static_cast<T>(x / div), static_cast<T>(y / div)};
	}

	template <class Tn>
	tuple_2<T>& operator/=(const Tn& div){
		x = static_cast<T>(x / div);
		y = static_cast<T>(y / div);
		return *this;
	}

	bool operator==(const tuple_2& comp){
		return (x == comp.x && y == comp.y);
	}

	bool operator!=(const tuple_2& comp){
		return (x != comp.x || y != comp.y);
	}

	T distance(){
		return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
	}
};

using vector = tuple_2<float>;
using point = tuple_2<int>;

#endif