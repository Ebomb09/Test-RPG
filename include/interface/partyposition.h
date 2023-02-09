#ifndef GAME_POSITION_SELECT_H
#define GAME_POSITION_SELECT_H

#include "interface/base.h"
#include "character.h"

struct partyposition : interface{

	character* select;
	int position;

	void set(character* ch);

	void update(game* Game);
	void draw(game* Game);
};

#endif