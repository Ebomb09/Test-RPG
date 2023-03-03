#ifndef GAME_MOVES_H
#define GAME_MOVES_H

#include <vector>
#include <string>
#include "stats.h"

class move{

	/* Characteristics of the move */
	struct scale{
		statistics::name from_name;
		double from_amount;

		statistics::name to_name;
	};
	std::vector<scale> scalings;

public:
	std::string asset;
	std::string name;

	move(std::string _name = "", std::string _asset = "", std::vector<scale> _scalings = {});

	void deal(statistics* from, statistics* to);
	int query_deal(statistics::name query, statistics* from, statistics* to);
};

#endif