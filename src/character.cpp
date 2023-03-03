#include "character.h"

character::character(std::string _name, std::string _asset,
		statistics _stats, 
		std::vector<move*> _learn,
		std::vector<move*> _compatible
		){
	name = _name;
	asset = _asset;
	stats = _stats;
	status = _stats;
	learned_moves = _learn;
	compatible_moves = _compatible;
}