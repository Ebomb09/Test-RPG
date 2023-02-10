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
#include "interface/partyposition.h"
#include "interface/battle.h"

#include "character.h"

class game : public input, public video, public audio{

	bool game_loop;
	long frames_per_second;
	double delta_time;

	mainmenu MainMenu;
	messagebox MessageBox;
	inputbox InputBox;
	worldmap WorldMap;
	partyposition PartyPosition;
	battle Battle;
	std::list<interface*> active_interfaces;

	void init();

public:
	game();
	~game();

	enum Archetype{
		WizardCat,
		Total
	};
	character characters[Archetype::Total];

	static const int max_party_size = 4;
	character* party[max_party_size];

	void load_Party(std::string fname="");

	void load_MainMenu();
	void load_MessageBox(std::string section);
	std::string load_InputBox(std::string prompt, std::string default_string="", int limit=32);
	void load_WorldMap(std::string map);
	int load_PartyPosition(character* ch);
	bool load_Battle();
	void load_Return();

	void run(interface* watch=NULL);
	void stop();

	double delta_Time();
};

#endif