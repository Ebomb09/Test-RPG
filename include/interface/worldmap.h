#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include <string>
#include "interface/base.h"

struct worldmap : interface{

	int x, y;

	void update();
	void draw();

	bool load_Map(std::string map);
};

#endif