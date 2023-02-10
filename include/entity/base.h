#ifndef GAME_WORLD_ENTITY_H 
#define GAME_WORLD_ENTITY_H

#include <string>
#include "vector.h"

struct game;
struct worldmap;

struct entity{

	point position;

	virtual bool interact(game* Game, worldmap* World);
	virtual void update(game* Game, worldmap* World);
	virtual void draw(game* Game, worldmap* World);
};

#endif