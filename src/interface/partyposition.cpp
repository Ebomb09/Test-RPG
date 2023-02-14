#include "interface/partyposition.h"
#include "game.h"

void partyposition::set(character* ch){
	select = ch;
	position = 0;
}

int partyposition::get(){
	return position;
}

void partyposition::update(game* Game){

	if(Game->key_Pressed(SDL_SCANCODE_UP)){

		position --;

		if(position < 0)
			position = game::characters::maxpartysize-1;
	}

	if(Game->key_Pressed(SDL_SCANCODE_DOWN)){

		position ++;

		if(position >= game::characters::maxpartysize)
			position = 0;
	}

	if(Game->key_Pressed(SDL_SCANCODE_SPACE)){

		if(select){

			// Swap if the selected character is already in the party
			for(int i = 0; i < game::characters::maxpartysize; i ++){

				if(i != position && Game->Party[i] == select){
					Game->Party[i] = Game->Party[position];
					break;
				}
			}
		}

		Game->Party[position] = select;
		Game->load_Return();
	}

	if(Game->key_Pressed(SDL_SCANCODE_ESCAPE)){
		position = -1;
		Game->load_Return();
	}
}

void partyposition::draw(game* Game){

	Game->draw_Text(320, 32, "Make your party", "DotGothic16-Regular.ttf", 24);

	Game->draw_Colour(255, 0, 255, 255);

	for(int i = 0; i < game::characters::maxpartysize; i ++){

		if(Game->Party[i])
			Game->draw_TextureClip(
				16, 
				16 + i * 80, 
				1, 0,
				32, 32,
				2, 2,
				Game->Party[i]->asset
				);

		Game->draw_Rectangle(16, 16 + i * 80, 64, 64);
	}

	Game->draw_Colour(0, 0, 255, 255);

	Game->draw_Line(80, 48 + position * 80, 128, 48 + position * 80);
	Game->draw_Line(80, 48 + position * 80, 100, 48 + position * 80 - 20);
	Game->draw_Line(80, 48 + position * 80, 100, 48 + position * 80 + 20);

	Game->draw_TextureClip(128, 16 + position * 80, 1, 0, 32, 32, 2, 2, select->asset);
	Game->draw_Colour(0, 0, 0, 255);
	Game->draw_Rectangle(128, 16 + position * 80, 64, 64);
}