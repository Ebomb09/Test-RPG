#include "entity/npc.h"
#include "game.h"

npc::npc(int x, int y, std::string _script, std::string _character){
	position = {x, y};
	script = _script;
	character = _character;
	solid = true;
	what = type::NPC;
}

bool npc::interact(game* Game, worldmap* World){

	Game->load_MessageBox(script);

	return true;
}

void npc::draw(game* Game, worldmap* World){

	if(character == "None" || character == "")
		return;

	std::string asset = "";

	for(auto& ch : Game->Characters){
		
		if(character == ch.defined_name){
			asset = ch.asset;
			break;
		}
	}

	Game->draw_TextureClip(
		position.x * 64, position.y * 64,
		0, 0,
		32, 32,
		2, 2,
		asset
		);
}