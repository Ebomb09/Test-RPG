#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <list>

#include "video.h"
#include "input.h"

#include "interface/mainmenu.h"
#include "interface/inputbox.h"

#include "character.h"

class game : public input, public video{

	bool game_loop;

	mainmenu MainMenu;
	inputbox InputBox;
	std::list<interface*> active_interfaces;

	void init();

public:
	game();
	~game();

	character Party[4];

	void load_MainMenu();
	void load_InputBox(callbackFn callback);
	void load_Return();
	void run();
	void stop();
};

#endif