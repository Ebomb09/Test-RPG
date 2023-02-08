#ifndef GAME_WORLD_PLAYER_H
#define GAME_WORLD_PLAYER_H

#include "entity/base.h"

struct player : entity{

	player(int _x, int _y);

	void update(game* Game, worldmap* World);
	void draw(game* Game, worldmap* World);
};

#endif