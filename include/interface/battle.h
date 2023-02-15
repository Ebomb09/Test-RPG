#ifndef GAME_BATTLE_H
#define GAME_BATTLE_H

#include "interface/base.h"
#include "character.h"
#include "delay.h"
#include "vector.h"

#include <vector>

struct action{

	enum{
		none,
		move,
		attack
	};
	int type = none;
	point transition;
};

struct actor{
	character* who;
	statistics status;
	point position;
	delay<action> work;
};

struct battle : interface{

	struct cursor{
		enum{
			none,
			select_attack,
			select_target
		};
		int mode;
		int position;
		int attack;
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

	void set(game* Game);
	bool get();

	void update(game* Game);
	void draw(game* Game);
};

#endif