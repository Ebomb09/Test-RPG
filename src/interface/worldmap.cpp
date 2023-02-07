#include <fstream>
#include <iostream>
#include "interface/worldmap.h"

void worldmap::update(){

}

void worldmap::draw(){

}

bool worldmap::load_Map(std::string map){

	// Open file
	std::fstream file(map, std::ios_base::in);

	if(file.fail()){
		file.close();
		return false;
	}

	while(!file.eof()){
		int x, y, type;

		file >> x;
		file >> y;
		file >> type;

		if(file.fail()){
			file.close();
			return false;

		}else{
			std::cout << x << ':' << y << ':' << type << '\n';
		}
	}

	file.close();

	return true;
}