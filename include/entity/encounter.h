#ifndef GAME_ENCOUNTER_H
#define GAME_ENCOUNTER_H

#include "entity/base.h"

struct encounter : entity{

	encounter(int x, int y);

	bool interact(game* Game, worldmap* World);
	void draw(game* Game, worldmap* World);
};

#endif