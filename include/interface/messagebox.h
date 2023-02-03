#ifndef GAME_MESSAGE_BOX_H
#define GAME_MESSAGE_BOX_H

#include "dialogue.h"
#include "interface/base.h"

struct messagebox : interface, handler{

	void update();
	void draw();
};


#endif