#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <string>
#include "interface/base.h"
#include "delay.h"

struct inputbox : interface{
	std::string prompt;
	int limit;
	std::string icon;

	delay<bool> faded;

	void set(game* Game, std::string prompt_string, std::string default_string = "", int limit_string = 32, std::string _icon = "");

	void update(game* Game);
	void draw(game* Game);
};

#endif