#ifndef GAME_VECTOR_H
#define GAME_VECTOR_H

template <class T>
struct tuple_2{

	T x = 0; 
	T y = 0;

	tuple_2 operator+(const tuple_2<T>& add){
		return tuple_2{x + add.x, y + add.y};
	}

	tuple_2& operator+=(const tuple_2<T>& add){
		x += add.x;
		y += add.y;
		return *this;
	}

	tuple_2 operator-(const tuple_2<T>& sub){
		return tuple_2{x - sub.x, y - sub.y};
	}

	tuple_2& operator-=(const tuple_2<T>& sub){
		x -= sub.x;
		y -= sub.y;
		return *this;
	}

	bool operator==(const tuple_2<T>& comp){
		return (x == comp.x && y == comp.y);
	}

	bool operator!=(const tuple_2<T>& comp){
		return (x != comp.x || y != comp.y);
	}
};

using vector2 = tuple_2<float>;
using point = tuple_2<int>;

#endif