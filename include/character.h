#ifndef GAME_CHARACTERS_H
#define GAME_CHARACTERS_H

#include <vector>
#include <string>
#include "stats.h"
#include "move.h"

struct character{
	std::string asset;
	std::string name;

	statistics status;	// Current stats
	statistics stats;	// Overall(max) stats

	std::vector<move*> learned_moves;
	std::vector<move*> compatible_moves; 

	character(std::string _name = "", std::string _asset = "",
		statistics _stats = {},
		std::vector<move*> _learn = {},
		std::vector<move*> _compatible = {}
		);
};

#endif 