#include <fstream>
#include "interface/worldmap.h"
#include "game.h"

void worldmap::update(game* Game){

	for(int i = 0; i < entities.size(); i ++)
		entities[i]->update(Game, this);
}

void worldmap::draw(game* Game){

	Game->draw_Text(16, 16, map_name, "DotGothic16-Regular.ttf", 13);

	for(int i = 0; i < entities.size(); i ++)
		entities[i]->draw(Game, this);
}

bool worldmap::load_Map(std::string map){

	// Open file
	std::fstream file(map, std::ios_base::in);

	if(file.fail()){
		file.close();
		return false;
	}

	while(!file.eof()){
		file.get();
	}

	file.close();
	map_name = map;

	return true;
}