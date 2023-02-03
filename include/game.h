#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <list>

#include "video.h"
#include "input.h"

#include "interface/mainmenu.h"
#include "interface/messagebox.h"
#include "interface/inputbox.h"

#include "character.h"

class game : public input, public video{

	bool game_loop;
	double frames_per_second;

	mainmenu MainMenu;
	messagebox MessageBox;
	inputbox InputBox;
	std::list<interface*> active_interfaces;

	void init();

public:
	game();
	~game();

	character Party[4];

	void load_MainMenu(callbackFn callback=NULL);
	void load_MessageBox(std::string section, callbackFn callback=NULL);
	void load_InputBox(callbackFn callback=NULL);
	void load_Return();
	void run();
	void stop();
};

#endif