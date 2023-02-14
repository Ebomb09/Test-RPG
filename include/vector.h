#ifndef GAME_VECTOR_H
#define GAME_VECTOR_H

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
		return tuple_2<T>{x * mult, y * mult};
	}

	template <class Tn>
	tuple_2<T>& operator*=(const Tn& mult){
		x *= mult;
		y *= mult;
		return *this;
	}

	template <class Tn>
	tuple_2<T> operator/(const Tn& div){
		return tuple_2<T>{x / div, y / div};
	}

	template <class Tn>
	tuple_2<T>& operator/=(const Tn& div){
		x /= div;
		y /= div;
		return *this;
	}

	bool operator==(const tuple_2& comp){
		return (x == comp.x && y == comp.y);
	}

	bool operator!=(const tuple_2& comp){
		return (x != comp.x || y != comp.y);
	}
};

using vector = tuple_2<float>;
using point = tuple_2<int>;

#endif