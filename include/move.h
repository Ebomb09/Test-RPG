#ifndef GAME_MOVES_H
#define GAME_MOVES_H

#include <string>
#include "stats.h"

struct move{
	std::string asset;
	std::string name;
	statistics scaling;
};

#endif