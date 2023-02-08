#include "entity/player.h"
#include "game.h"

player::player(int _x, int _y){
	x = _x;
	y = _y;
}

void player::update(game* Game, worldmap* World){

	if(Game->key_Pressed(SDL_SCANCODE_UP))
		y -= 1;

	if(Game->key_Pressed(SDL_SCANCODE_DOWN))
		y += 1;

	if(Game->key_Pressed(SDL_SCANCODE_LEFT))
		x -= 1;

	if(Game->key_Pressed(SDL_SCANCODE_RIGHT))
		x += 1;

	if(Game->key_Pressed(SDL_SCANCODE_SPACE)){

		for(entity* ent: World->entities){

			if(ent == this)
				continue;

			if(ent->x == x && ent->y == y)
				ent->interact(Game, World);
		}
	}
}

void player::draw(game* Game, worldmap* World){
	Game->draw_Colour(255, 255, 0, 255);
	Game->draw_Rectangle(x * 16, y * 16, 16, 16);
	Game->draw_Text(x * 16, y * 16, "ply", "DotGothic16-Regular.ttf", 16);
}