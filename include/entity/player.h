#ifndef GAME_WORLD_PLAYER_H
#define GAME_WORLD_PLAYER_H

#include "entity/base.h"
#include "delay.h"

struct player : entity{

	delay<point> move;
	point facing;

	player(int x, int y);

	void update(game* Game, worldmap* World);
	void draw(game* Game, worldmap* World);

	void try_Move(worldmap* World, point position);
};

#endif