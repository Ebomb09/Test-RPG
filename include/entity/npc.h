#ifndef GAME_WORLD_NPC_H
#define GAME_WORLD_NPC_H

#include <string>
#include "entity/base.h"

struct npc : entity{

	std::string script;

	npc(int _x, int _y, std::string _script);

	bool interact(game* Game, worldmap* World);
	void draw(game* Game, worldmap* World);
};

#endif