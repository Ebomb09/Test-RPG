#ifndef WORLD_MAP_H
#define WORLD_MAP_H

#include <string>
#include <vector>
#include "interface/base.h"

struct object{
	int x, y;
	char name[80];
	char data[80];
	char texture[80];
};

struct worldmap : interface{

	int x, y;
	std::vector<object> objects;

	void update();
	void draw();

	bool load_Map(std::string map);
};

#endif