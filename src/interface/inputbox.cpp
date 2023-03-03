#include <iostream>
#include "game.h"
#include "interface/inputbox.h"

void inputbox::set(game* Game, std::string prompt_string, std::string default_string, int limit_string, std::string _icon){
	Game->set_string(default_string);
	limit = limit_string;
	prompt = prompt_string;
	icon = _icon;

	faded.set(1, true);
}

void inputbox::update(game* Game){

	std::string output = Game->get_string();

	if(output.size() > limit)
		Game->set_string(output.substr(0, limit));

	// Fade out of input box if trying to escape
	if(Game->key_Pressed(SDL_SCANCODE_RETURN))
		faded.set(1, false);

	// Done fading so return
	if(faded.done() && !faded.get())
		Game->load_Return();

	faded.increment(Game->delta_Time());
}

void inputbox::draw(game* Game){

	if(faded.done() && faded.get()){
		Game->clear_Buffer(255, 255, 255, 255);

	}else{

		if(faded.get()){
			Game->draw_Colour(255, 255, 255, 255 * faded.percent());
			Game->draw_FillRectangle(0, 0, 640, 480);

		}else{
			Game->draw_Colour(255, 255, 255, 255 - 255 * faded.percent());
			Game->draw_FillRectangle(0, 0, 640, 480);
			return;
		}
	}

	if(icon != "")
		Game->draw_TextureClip(
			256, 240,
			1, 0,
			32, 32,
			2, 2,
			icon
			);

	Game->draw_Text(320, 240, prompt, "DotGothic16-Regular.ttf", 24);
	Game->draw_Text(320, 264, Game->get_string(), "DotGothic16-Regular.ttf", 16);
}