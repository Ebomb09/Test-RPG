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

public:
	game();
	~game();

	/* Character / Party */
	struct characters{
		enum{
			wizardcat,
			total,
			maxpartysize = 4
		};
	};
	character Characters[characters::total];
	character* Party[characters::maxpartysize];

	void load_Party(std::string fname="");

	/* Enemies */
	struct enemies{
		enum{
			slime,
			total
		};
	};
	character Enemies[enemies::total];

	void load_Enemies();

	/* Movelist */
	struct moves{
		enum{
			attack,
			item,
			fire,
			thunder,
			ice,
			total
		};
	};
	move Moves[moves::total];

	void load_Moves();

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