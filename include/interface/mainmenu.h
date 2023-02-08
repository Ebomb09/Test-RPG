#ifndef INTERFACE_MAIN_MENU_H
#define INTERFACE_MAIN_MENU_H

#include "interface/base.h"

struct mainmenu : interface{

	void update(game* Game);
	void draw(game* Game);
};

#endif