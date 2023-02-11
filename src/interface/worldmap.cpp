#include <fstream>
#include "interface/worldmap.h"
#include "game.h"
#include "entity/player.h"
#include "entity/npc.h"
#include "entity/encounter.h"

worldmap::~worldmap(){
	clear();
}

void worldmap::update(game* Game){

	for(int i = 0; i < entities.size(); i ++)
		entities[i]->update(Game, this);
}

void worldmap::draw(game* Game){

	Game->draw_Text(16, 16, map_name, "DotGothic16-Regular.ttf", 16);

	for(int i = 0; i < entities.size(); i ++)
		entities[i]->draw(Game, this);
}

void worldmap::clear(){

	for(int i = 0; i < entities.size(); i ++)
		delete entities[i];

	entities.clear();
}

std::vector<entity*> worldmap::colliding(entity* source, point transition, bool solid, entity::type type){
	std::vector<entity*> collisions;

	for(int i = 0; i < entities.size(); i ++){

		if(entities[i] == source)
			continue;

		if(source->position + transition == entities[i]->position)

			if((entities[i]->solid && solid) || !solid)

				if(entities[i]->what == type || type == entity::type::Generic)

					collisions.push_back(entities[i]);
			
	}
	return collisions;
}

bool worldmap::load_Map(std::string map){

	clear();

	// Open file
	std::fstream file(map, std::ios_base::in);

	if(file.fail()){
		file.close();
		return false;
	}

	while(file.good()){
		std::string name;

		if(file >> name){

			if(name == "player"){
				int x, y;

				if(file >> x >> y)
					entities.push_back(new player(x, y));
			}	

			if(name == "npc"){
				int x, y;
				std::string script;

				if(file >> x >> y >> script)
					entities.push_back(new npc(x, y, script));
			}

			if(name == "encounter"){
				int x, y;

				if(file >> x >> y)
					entities.push_back(new encounter(x, y));
			}
		}
	}

	file.close();
	map_name = map;

	return true;
}