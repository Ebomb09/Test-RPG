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
		intro,
		attack
	};
	int type = none;
	point transition;
};

struct actor{
	character* who;
	point position;
	delay<action> action;
};

struct battle : interface{

	int cursor;

	enum{
		waiting_to_complete,
		inputting_actions
	};
	int mode;

	std::vector<actor> actors;

	void set(game* Game);
	bool get();

	void update(game* Game);
	void draw(game* Game);
};

#endif