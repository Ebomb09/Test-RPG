#include "interface/battle.h"
#include "game.h"
#include <cmath>

void battle::set(){

	start = {320, 240};

	for(int i = 0; i < 4; i ++)
		transition[i].set(0.5, {480 + i * 16 - start.x, 64 + i * 80 - start.y});
}

bool battle::get(){
	return true;
}

void battle::update(game* Game){

	if(Game->key_Pressed(SDL_SCANCODE_ESCAPE))
		Game->load_Return();

	for(int i = 0; i < Game->max_party_size; i ++){
		transition[i].increment(Game->delta_Time());
	}
}

void battle::draw(game* Game){

	for(int i = 0; i < Game->max_party_size; i ++){

		if(Game->party[0]){

			Game->draw_TextureClip(
				start.x + transition[i].get().x * transition[i].percent(), 
				start.y + transition[i].get().y * transition[i].percent() - 120 * std::sin(M_PI * transition[i].percent()),
				0, 0,
				32, 32,
				2, 2,
				Game->party[0]->asset
				);
		}
	}
}