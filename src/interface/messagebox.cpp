#include "interface/messagebox.h"
#include "game.h"

void messagebox::proceed(){
	position = 0;
	next();
}

void messagebox::check(game* Game){

	// Set the built-in variables
	int size = 0;

	for(int i = 0; i < characters::total; i ++){

		// Default initialization character name
		std::string name = Game->Characters[i].defined_name;

		// Check if the party member has requested to join
		if(getvar(("join_" + name).c_str()) == 1){
			assign(("join_" + name).c_str(), 0);
			Game->Characters[i].name = Game->load_InputBox("Name your character", name, Game->Characters[i].asset, 32);
			Game->load_PartyPosition(&Game->Characters[i]);
		}

		// Check if character is a member of the party
		if(Game->is_PartyMember(&Game->Characters[i])){
			size++;
			assign(("in_party_" + name).c_str(), 1);

		}else{
			assign(("in_party_" + name).c_str(), 0);
		}
	}

	// Assign the built-in variables
	assign("party_size", size);
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

	if(Game->front_Interface() != this)
		return;

	Game->draw_Colour(128, 0, 255, 128);
	Game->draw_FillRectangle(0, 240, 640, 240);

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