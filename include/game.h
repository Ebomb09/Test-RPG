#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include "interface/base.h"
#include "character.h"

class game{

	character party[4];

	enum INTERFACES{
		MAIN_MENU,
		WORLD_MAP,
		MESSAGE_BOX,
		INPUT_BOX,
		TOTAL
	};
	interface* loaded_interfaces[INTERFACES::TOTAL];
	interface* active_interfaces[INTERFACES::TOTAL];

	void load_mainmenu();
	void load_worldmap();
	void load_messagebox();
	void load_inputbox();

public:
	game();
	~game();
};

#endif