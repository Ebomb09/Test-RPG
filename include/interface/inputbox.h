#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <string>
#include "interface/base.h"

struct inputbox : interface{
	std::string prompt;
	int limit;

	void set(game* Game, std::string prompt_string, std::string default_string, int limit_string);

	void update(game* Game);
	void draw(game* Game);
};

#endif