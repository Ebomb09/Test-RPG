#include "interface/messagebox.h"
#include "game.h"

void messagebox::update(){

	switch(current()){

		case dialogue::Dialogue:{

			if(Game->key_Pressed(SDL_SCANCODE_SPACE))
				next();
			break;
		}

		case dialogue::Option: {

			if(Game->key_Pressed(SDL_SCANCODE_SPACE))
				next();
			break;			
		}

		default: {
			Game->load_Return();
			break;
		}
	}
}

void messagebox::draw(){

	switch(current()){

		case dialogue::Dialogue: {
			Game->draw_TextClip(0, 240, 640, 26, getSpeaker(), "DotGothic16-Regular.ttf", 48);
			Game->draw_TextClip(0, 288, 640, 480-288, getText(), "DotGothic16-Regular.ttf", 36);
			break;
		}

		case dialogue::Option: {

			for(int i = 0; i < getOptionCount(); i ++){
				Game->draw_TextClip(0, 240+16*i, 640, 16, std::to_string(i) + ". " + getOptionText(i), "DotGothic16-Regular.ttf", 16);
			}
		}
	}
}