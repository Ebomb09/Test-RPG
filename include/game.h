#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <list>

#include "interface/mainmenu.h"
#include "interface/inputbox.h"
#include "character.h"

class game{

	character party[4];

	mainmenu MainMenu;
	inputbox InputBox;
	std::list<interface*> active_interfaces;

public:
	game();
	~game();

	bool game_loop;

	void init();
	void load_MainMenu();
	void load_InputBox(callbackFn callback);
	void load_Return();
	void run();
};

#endif