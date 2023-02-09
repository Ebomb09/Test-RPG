#include <iostream>
#include "game.h"
#include "interface/inputbox.h"

void inputbox::set(game* Game, std::string prompt_string, std::string default_string, int limit_string){
	Game->set_string(default_string);
	limit = limit_string;
	prompt = prompt_string;
}

void inputbox::update(game* Game){

	std::string output = Game->get_string();

	if(output.size() > limit)
		Game->set_string(output.substr(0, limit));

	if(Game->key_Pressed(SDL_SCANCODE_RETURN))
		Game->load_Return();
}

void inputbox::draw(game* Game){

	Game->draw_Text(320, 240, prompt, "DotGothic16-Regular.ttf", 24);
	Game->draw_Text(320, 264, Game->get_string(), "DotGothic16-Regular.ttf", 16);
}