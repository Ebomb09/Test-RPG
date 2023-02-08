#include <cstring>
#include <fstream>
#include <string>
#include <iostream>
#include "interface/worldmap.h"

void worldmap::update(game* Game){

}

void worldmap::draw(game* Game){

}

bool worldmap::load_Map(std::string map){

	// Open file
	std::fstream file(map, std::ios_base::in);

	if(file.fail()){
		file.close();
		return false;
	}

	while(!file.eof()){
		std::cin.get();
	}

	file.close();

	return true;
}