#include "interface/messagebox.h"
#include "game.h"

void messagebox::proceed(){
	position = 0;
	next();
}

void messagebox::update(game* Game){

	switch(current()){

		case dialogue::Dialogue:{

			if(Game->key_Pressed(SDL_SCANCODE_SPACE))
				proceed();
			break;
		}

		case dialogue::Option: {

			if(Game->key_Pressed(SDL_SCANCODE_DOWN)){
				position ++;

				if(position >= getOptionCount())
					position = 0;
			}

			if(Game->key_Pressed(SDL_SCANCODE_UP)){
				position --;

				if(position < 0)
					position = getOptionCount() - 1;
			}

			if(Game->key_Pressed(SDL_SCANCODE_SPACE) && select(position))
				proceed();

			break;			
		}

		default: {
			Game->load_Return();
			break;
		}
	}
}

void messagebox::draw(game* Game){

	switch(current()){

		case dialogue::Dialogue: {
			Game->draw_TextClip(0, 240, 640, 26, getSpeaker(), "DotGothic16-Regular.ttf", 48);
			Game->draw_TextClip(0, 288, 640, 480-288, getText(), "DotGothic16-Regular.ttf", 36);
			break;
		}

		case dialogue::Option: {

			for(int i = 0; i < getOptionCount(); i ++){
				Game->draw_TextClip(0, 240+36*i, 640, 16, std::to_string(i) + ". " + getOptionText(i), "DotGothic16-Regular.ttf", 36);
			}

			Game->draw_Text(480, 240+36*position, "<-", "DotGothic16-Regular.ttf", 36);
		}
	}
}