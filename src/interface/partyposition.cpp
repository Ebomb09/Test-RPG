#include "interface/partyposition.h"
#include "game.h"

void partyposition::set(character* ch){
	select = ch;
	position = 0;
}

void partyposition::update(game* Game){

	if(Game->key_Pressed(SDL_SCANCODE_UP)){

		position --;

		if(position < 0)
			position = Game->max_party_size-1;
	}

	if(Game->key_Pressed(SDL_SCANCODE_DOWN)){

		position ++;

		if(position >= Game->max_party_size)
			position = 0;
	}

	if(Game->key_Pressed(SDL_SCANCODE_SPACE)){

		if(select){

			// Swap if the selected character is already in the party
			for(int i = 0; i < Game->max_party_size; i ++){

				if(i != position && Game->party[i] == select){
					Game->party[i] = Game->party[position];
					break;
				}
			}
		}

		Game->party[position] = select;
		Game->load_Return();
	}

	if(Game->key_Pressed(SDL_SCANCODE_ESCAPE))
		Game->load_Return();
}

void partyposition::draw(game* Game){

	Game->draw_Text(320, 32, "Make your party", "DotGothic16-Regular.ttf", 24);

	Game->draw_Colour(255, 0, 255, 255);

	for(int i = 0; i < Game->max_party_size; i ++){
		Game->draw_Rectangle(16, 16 + i * 80, 64, 64);

		if(Game->party[i])
			Game->draw_Text(16, 16 + i * 80, Game->party[i]->name, "DotGothic16-Regular.ttf", 26);
	}

	Game->draw_Colour(0, 0, 255, 255);

	Game->draw_Line(80, 48 + position * 80, 128, 48 + position * 80);
	Game->draw_Line(80, 48 + position * 80, 100, 48 + position * 80 - 20);
	Game->draw_Line(80, 48 + position * 80, 100, 48 + position * 80 + 20);
}