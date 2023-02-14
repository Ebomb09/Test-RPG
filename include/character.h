#ifndef GAME_CHARACTERS_H
#define GAME_CHARACTERS_H

#include <vector>
#include <string>
#include "stats.h"
#include "move.h"

struct character{
	std::string asset;
	std::string name;
	stats stats;
	std::vector<move*> learned_moves;
	std::vector<move*> compatible_moves; 
};

#endif 