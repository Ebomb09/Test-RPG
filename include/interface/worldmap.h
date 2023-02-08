#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include <string>
#include <vector>
#include "interface/base.h"
#include "entity/base.h"

struct worldmap : interface{

	entity Player;
	std::vector<entity*> entities;

	void update(game* Game);
	void draw(game* Game);

	bool load_Map(std::string map);
};

#endif