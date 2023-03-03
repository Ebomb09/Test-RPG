#include "entity/player.h"
#include "game.h"

player::player(int x, int y){
	position = {x, y};
	solid = true;
	what = type::Player;
}

void player::update(game* Game, worldmap* World){

	if(move.done()){
		position += move.get();
		move.get() = {0, 0};
	}

	if(Game->key_Held(SDL_SCANCODE_UP))
		try_Move(World, {0, -1});

	if(Game->key_Held(SDL_SCANCODE_DOWN))
		try_Move(World, {0, 1});
	
	if(Game->key_Held(SDL_SCANCODE_LEFT))
		try_Move(World, {-1, 0});
	
	if(Game->key_Held(SDL_SCANCODE_RIGHT))
		try_Move(World, {1, 0});

	if(Game->key_Pressed(SDL_SCANCODE_SPACE)){

		for(auto& ent : World->colliding(this, facing, false, type::NPC))
			ent->interact(Game, World);

		for(auto& ent : World->colliding(this, {}, false, type::Encounter))
			ent->interact(Game, World);
	}

	move.increment(Game->delta_Time());
}

void player::draw(game* Game, worldmap* World){

	// Draw first party member
	std::string asset = "data/textures/ghost.png";

	for(int i = 0; i < characters::maxpartysize; i ++){

		if(Game->Party[i]){
			asset = Game->Party[i]->asset;
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

void player::try_Move(worldmap* World, point position){
	facing = position;

	if(World->colliding(this, position, true).size() == 0)
		move.set(0.25, position);
}