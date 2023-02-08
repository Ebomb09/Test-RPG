#ifndef GAME_WORLD_ENTITY_H 
#define GAME_WORLD_ENTITY_H

#include <string>

struct game;
struct worldmap;

struct entity{
	int x, y;
	std::string texture;

	virtual bool interact(entity* Caller);
	
	virtual void update(game* Game, worldmap* World);
	virtual void draw(game* Game, worldmap* World);
};

#endif