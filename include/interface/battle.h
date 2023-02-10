#ifndef GAME_BATTLE_H
#define GAME_BATTLE_H

#include "interface/base.h"
#include "delay.h"
#include "vector.h"

struct battle : interface{

	point start;
	delay<point> transition[4];

	void set();
	bool get();

	void update(game* Game);
	void draw(game* Game);
};

#endif