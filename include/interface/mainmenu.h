#ifndef INTERFACE_MAIN_MENU_H
#define INTERFACE_MAIN_MENU_H

#include "interface/base.h"

struct mainmenu : interface{
	mainmenu();

	void update();
	void draw();

	static void get_string(interface* it, void** args);
};

#endif