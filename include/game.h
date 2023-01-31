#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <list>

#include "interface/mainmenu.h"
#include "character.h"

class game{

	character party[4];

	mainmenu MainMenu;
	//worldmap WorldMap;

	std::list<interface*> active_interfaces;

public:
	game();
	~game();

	void init();
	void load_MainMenu();
	void run();
};

#endif