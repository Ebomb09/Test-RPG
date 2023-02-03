#include "interface/messagebox.h"
#include "game.h"

void messagebox::update(){

	switch(current()){

		case Dialogue:{

			if(Game->key_Pressed(SDL_SCANCODE_SPACE))
				next();
			break;
		}

		case Option: {

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

		case Dialogue: {
			Game->draw_Text(0, 240, getSpeaker(), "DotGothic16-Regular.ttf", 26);
			Game->draw_Text(0, 266, getText(), "DotGothic16-Regular.ttf", 16);
			break;
		}

		case Option: {

			for(int i = 0; i < getOptionCount(); i ++){
				Game->draw_Text(0, 240+16*i, std::to_string(i) + ". " + getOptionText(i), "DotGothic16-Regular.ttf", 16);
			}
		}
	}
}