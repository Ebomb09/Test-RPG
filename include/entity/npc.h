#ifndef GAME_WORLD_NPC_H
#define GAME_WORLD_NPC_H

#include <string>
#include "entity/base.h"

struct npc : entity{

	std::string script, character;

	npc(int x, int y, std::string _script, std::string _character);

	bool interact(game* Game, worldmap* World);
	void draw(game* Game, worldmap* World);
};

#endif