#include "move.h"
#include <iostream>

move::move(std::string _name, std::string _asset, std::vector<scale> _scalings){
	name = _name;
	asset = _asset;
	scalings = _scalings;
}

/* Affect the statistics of a destination _to_ with the statistics of a source _from_ */
void move::deal(statistics* from, statistics* to){

	for(auto& scaling : scalings){

		// Get pointers to which stats are affected
		int* from_stat = from->get_stat(scaling.from_name);
		int* to_stat = to->get_stat(scaling.to_name);

		if(!from_stat || !to_stat){
			std::cerr << "Error: Invalid statistic names provided\n";
			return;
		}

		// Affect the stat by the amount from source
		(*to_stat) += (*from_stat) * scaling.from_amount;
	}
}

/* Find the deal stats change on the queried stat name */
int move::query_deal(statistics::name query, statistics* from, statistics* to){

	int total = 0;

	for(auto& scaling : scalings){

		if(scaling.to_name != query)
			continue;

		// Get pointers to which stats are affected
		int* from_stat = from->get_stat(scaling.from_name);
		int* to_stat = to->get_stat(scaling.to_name);

		if(!from_stat || !to_stat){
			std::cerr << "Error: Invalid statistic names provided\n";
			return 0;
		}

		// Affect the stat by the amount from source
		total += (*from_stat) * scaling.from_amount;
	}
	return total;
}