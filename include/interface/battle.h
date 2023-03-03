#ifndef GAME_BATTLE_H
#define GAME_BATTLE_H

#include "interface/base.h"
#include "character.h"
#include "delay.h"
#include "move.h"
#include "vector.h"

#include <vector>

struct actor;

struct action{

	enum action_type{
		none,
		transition,
		attack
	};
	int type = none;

	/* Move */
	point where;

	/* Attack */
	actor* target = NULL;
	move* command = NULL;
};

struct actor{
	character* who;
	statistics status;
	point position;
	delay<action> work;
	int team;

	actor(character* _who, statistics _status, point _position, int _team);

	void act();
};

struct battle : interface{

	struct cursor{
		enum cursor_mode{
			none,
			select_attack,
			select_target
		};
		int mode;
		int position;
		int command;
		int target;
	}curse;

	void select_Cursor();
	void return_Cursor();
	void move_Cursor(point transition);
	void reset_Cursor(int mode, int position=0);
	void draw_Cursor(game* Game);

	enum{
		waiting_to_complete,
		inputting_actions
	};
	int mode;

	actor* next;
	std::vector<actor> actors;

	point start;

	int get_IndexFirstFromTeam(int team);

	void set(game* Game, point pos);
	bool get();

	void update(game* Game);
	void draw(game* Game);
};

#endif