#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <list>

#include "video.h"
#include "input.h"
#include "audio.h"

#include "interface/mainmenu.h"
#include "interface/messagebox.h"
#include "interface/inputbox.h"
#include "interface/worldmap.h"

#include "character.h"

class game : public input, public video, public audio{

	bool game_loop;
	double frames_per_second;

	mainmenu MainMenu;
	messagebox MessageBox;
	inputbox InputBox;
	worldmap WorldMap;
	std::list<interface*> active_interfaces;

	void init();
	void check_MessageBox();

public:
	game();
	~game();

	enum Archetype{
		Rogue,
		WizardCat,
		Total
	};
	character characters[Archetype::Total];
	character* party[4];

	void load_MainMenu(callbackFn callback=NULL);
	void load_MessageBox(std::string section, callbackFn callback=NULL);
	void load_InputBox(callbackFn callback=NULL);
	void load_WorldMap(std::string map, callbackFn callback=NULL);
	void load_Return();
	void run();
	void stop();
};

#endif