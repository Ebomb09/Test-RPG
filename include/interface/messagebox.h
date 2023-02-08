#ifndef GAME_MESSAGE_BOX_H
#define GAME_MESSAGE_BOX_H

#include "dialogue.h"
#include "interface/base.h"

struct messagebox : interface, dialogue::handler{

	void update(game* Game);
	void draw(game* Game);
};


#endif