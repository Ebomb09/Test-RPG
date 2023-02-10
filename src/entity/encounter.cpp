#include "entity/encounter.h"
#include "game.h"

encounter::encounter(int x, int y){
	position = {x, y};
}

void encounter::draw(game* Game, worldmap* World){

	Game->draw_Rectangle(position.x * 64, position.y * 64, 64, 64);
	Game->draw_Text(position.x * 64, position.y * 64, "encounter", "DotGothic16-Regular.ttf", 32);
}

bool encounter::interact(game* Game, worldmap* World){
	Game->load_Battle();
	return true;
}