#include <iostream>
#include <string>
#include "game.h"
#include "interface/mainmenu.h"

mainmenu::mainmenu(){

}

void mainmenu::update(){
	//std::cout << "I want a string\n";
	//Game->load_InputBox(&get_string);

}

void mainmenu::draw(){
	Game->draw_Line(10, 10, (Game->key_Held(SDL_SCANCODE_A)) ? 400 : 200, 300);

	Game->draw_Texture(32, 32, "test.bmp");
	Game->draw_Texture(128, 32, "test2.bmp");

	for(int t = 1; t < 10; t ++)
		Game->draw_Text(Game->mouse_PositionX(), Game->mouse_PositionY() + t, Game->get_string(), "DotGothic16-Regular.ttf", t * 4);
}

void mainmenu::get_string(interface* it, void* args[]){
	std::cout << "String entered " << *(std::string*)args[0] << '\n';
}