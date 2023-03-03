#ifndef GAME_POSITION_SELECT_H
#define GAME_POSITION_SELECT_H

#include "interface/base.h"
#include "character.h"

#include "delay.h"

struct partyposition : interface{

	character* select;
	int position;

	delay<bool> faded;

	void set(character* ch);
	int get();

	void update(game* Game);
	void draw(game* Game);
};

#endif