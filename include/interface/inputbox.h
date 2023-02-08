#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <string>
#include "interface/base.h"

struct inputbox : interface{
	std::string output;

	void update(game* Game);
	void draw(game* Game);
};

#endif