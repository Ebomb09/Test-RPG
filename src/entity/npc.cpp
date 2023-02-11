#include "entity/npc.h"
#include "game.h"

npc::npc(int x, int y, std::string _script){
	position = {x, y};
	script = _script;
	solid = true;
	what = type::NPC;
}

bool npc::interact(game* Game, worldmap* World){

	Game->load_MessageBox(script);

	return true;
}

void npc::draw(game* Game, worldmap* World){
	Game->draw_Colour(255, 255, 0, 255);
	Game->draw_Rectangle(position.x * 64, position.y * 64, 64, 64);
	Game->draw_Text(position.x * 64, position.y * 64, "npc", "DotGothic16-Regular.ttf", 32);
}