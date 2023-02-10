#include "entity/player.h"
#include "game.h"

player::player(int _x, int _y){
	position.x = _x;
	position.y = _y;
}

void player::update(game* Game, worldmap* World){

	if(move.done()){
		position.x += move.get().x;
		position.y += move.get().y;
		move.get() = {0, 0};
	}

	if(Game->key_Held(SDL_SCANCODE_UP))
		move.set(0.25, {0, -1});

	if(Game->key_Held(SDL_SCANCODE_DOWN))
		move.set(0.25, {0, 1});
	
	if(Game->key_Held(SDL_SCANCODE_LEFT))
		move.set(0.25, {-1, 0});
	
	if(Game->key_Held(SDL_SCANCODE_RIGHT))
		move.set(0.25, {1, 0});

	if(Game->key_Pressed(SDL_SCANCODE_SPACE)){

		for(entity* ent: World->entities){

			if(ent == this)
				continue;

			if(ent->position.x == position.x && ent->position.y == position.y)
				ent->interact(Game, World);
		}
	}

	move.increment(Game->delta_Time());
}

void player::draw(game* Game, worldmap* World){

	// Draw first party member
	std::string asset = "data/textures/ghost.png";

	for(int i = 0; i < Game->max_party_size; i ++){

		if(Game->party[i]){
			asset = Game->party[i]->asset;
			break;
		}
	}

	Game->draw_TextureClip(
		position.x * 64 + move.get().x * move.percent() * 64, 
		position.y * 64 + move.get().y * move.percent() * 64, 
		0, 0, 
		32, 32, 
		2, 2, 
		asset);
}