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
#include "move.h"

class game : public input, public video, public audio{

	/* Game control declarations */
	bool game_loop;
	long frames_per_second;
	double delta_time;

	/* Interfaces declarations */
	mainmenu MainMenu;
	messagebox MessageBox;
	inputbox InputBox;
	worldmap WorldMap;
	partyposition PartyPosition;
	battle Battle;
	std::list<interface*> active_interfaces;

	/* Init subsystems */
	void init();

	/* Movelist */
	enum class MoveList{
		Attack,
		Item,
		Fire,
		Thunder,
		Ice,
		Total
	};
	move moves[(int)MoveList::Total];

	void load_Moves();

public:
	game();
	~game();


	/* Character / Party */
	enum class Archetype{
		WizardCat,
		Total
	};
	character characters[(int)Archetype::Total];

	static const int max_party_size = 4;
	character* party[max_party_size];

	void load_Party(std::string fname="");

	/* Interface Runners */
	void load_MainMenu();
	void load_MessageBox(std::string section);
	std::string load_InputBox(std::string prompt, std::string default_string="", int limit=32);
	void load_WorldMap(std::string map);
	int load_PartyPosition(character* ch);
	bool load_Battle();
	void load_Return();

	/* Game control */
	void run(interface* watch=NULL);
	void stop();

	/* Time Calculations */
	double delta_Time();
};

#endif