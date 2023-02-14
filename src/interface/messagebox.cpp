#include "interface/messagebox.h"
#include "game.h"

void messagebox::proceed(){
	position = 0;
	next();
}

void messagebox::check(game* Game){

	// Check dialogue variables set that we want to
	// track. Such as items, characters, teleports, etc.

	if(getvar("join_WizardCat") == 1){
		assign("join_WizardCat", 0);
		Game->Characters[game::characters::wizardcat].name = Game->load_InputBox("Name your character", Game->Characters[game::characters::wizardcat].name);
		Game->load_PartyPosition(&Game->Characters[game::characters::wizardcat]);
	}

	// Set the built-in variables

	int size = 0;
	int wizardcat = 0;
	for(int i = 0; i < game::characters::maxpartysize; i ++){

		if(Game->Party[i])
			size++;

		if(Game->Party[i] == &Game->Characters[game::characters::wizardcat])
			wizardcat = 1;
	}

	assign("party_size", size);
	assign("in_party_WizardCat", wizardcat);
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
			check(Game);
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