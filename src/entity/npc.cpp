#include "entity/npc.h"
#include "game.h"

npc::npc(int _x, int _y, std::string _script){
	x = _x;
	y = _y;
	script = _script;
}

bool npc::interact(game* Game, worldmap* World){

	Game->load_MessageBox(script);

	return true;
}

void npc::draw(game* Game, worldmap* World){
	Game->draw_Colour(255, 255, 0, 255);
	Game->draw_Rectangle(x * 16, y * 16, 16, 16);
	Game->draw_Text(x * 16, y * 16, "npc", "DotGothic16-Regular.ttf", 16);
}