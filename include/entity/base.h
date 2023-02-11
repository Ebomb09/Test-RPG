#ifndef GAME_WORLD_ENTITY_H 
#define GAME_WORLD_ENTITY_H

#include <string>
#include "vector.h"

struct game;
struct worldmap;

struct entity{

	enum class type{
		Generic,
		NPC,
		Encounter,
		Player
	}what;

	point position;
	bool solid;

	entity();

	virtual bool interact(game* Game, worldmap* World);
	virtual void update(game* Game, worldmap* World);
	virtual void draw(game* Game, worldmap* World);
	type get_Type();
};

#endif