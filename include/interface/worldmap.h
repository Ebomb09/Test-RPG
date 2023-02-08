#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include <string>
#include <vector>
#include "interface/base.h"
#include "entity/base.h"

struct worldmap : interface{

	std::string map_name;
	std::vector<entity*> entities;

	~worldmap();

	void update(game* Game);
	void draw(game* Game);

	void clear();
	bool load_Map(std::string map);
};

#endif