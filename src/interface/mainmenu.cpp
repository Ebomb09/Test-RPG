#include <iostream>
#include <string>
#include "game.h"
#include "interface/mainmenu.h"

void mainmenu::update(game* Game){
	//std::cout << "I want a string\n";
	//Game->load_InputBox(&get_string);

	if(Game->key_Pressed(SDL_SCANCODE_SPACE)){
		Game->load_WorldMap("data/maps/test");
	}
}

void mainmenu::draw(game* Game){
	Game->draw_Text(10, 10, "Press Space to start the game!", "DotGothic16-Regular.ttf", 26);
}