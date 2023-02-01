#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <string>
#include "interface/base.h"

struct inputbox : interface{
	std::string output;
	inputbox();

	void update();
	void draw();
};

#endif