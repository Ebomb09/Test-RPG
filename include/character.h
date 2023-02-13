#ifndef GAME_CHARACTERS_H
#define GAME_CHARACTERS_H

#include <string>
#include "stats.h"

struct character{
	std::string asset;
	std::string name;
	stats stats; 
};

#endif 