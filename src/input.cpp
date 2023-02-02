#include "input.h"
#include "SDL_keycode.h"
#include "SDL_scancode.h"
#include <cctype>
#include <iostream>

input::input(){
	quit = false;
	reset_string();
}

input::~input(){
	SDL_QuitSubSystem(SDL_INIT_EVENTS);	
}

bool input::init(){
	return (SDL_InitSubSystem(SDL_INIT_EVENTS) == 0);
}

void input::refresh(std::map<const int, bool>& map){

	for(std::map<const int, bool>::iterator it = map.begin(); it != map.end(); it ++){
		(*it).second = false;
	}
}

char translate(char c){
	c = std::toupper(c);

	switch(c){
		case '`': c = '~'; break;
		case '1': c = '!'; break;
		case '2': c = '@'; break;
		case '3': c = '#'; break;
		case '4': c = '$'; break;
		case '5': c = '%'; break;
		case '6': c = '^'; break;
		case '7': c = '&'; break;
		case '8': c = '*'; break;
		case '9': c = '('; break;
		case '0': c = ')'; break;
		case '-': c = '_'; break;
		case '=': c = '+'; break;
		case '[': c = '{'; break;
		case ']': c = '}'; break;
		case '\\': c = '|'; break;
		case ';': c = ':'; break;
		case '\'': c = '"'; break;
		case ',': c = '<'; break;
		case '.': c = '>'; break;
		case '/': c = '?'; break;
	}

	return c;
}

void input::poll(){

	SDL_Event event;

	refresh(Pressed);
	refresh(Released);

	while(SDL_PollEvent(&event)){

		if(event.type == SDL_QUIT)
			quit = true;	

		if(event.type == SDL_KEYDOWN){
			Pressed[event.key.keysym.scancode] = true;
			Held[event.key.keysym.scancode] = true;

			// Input string control
			if(event.key.keysym.sym == SDLK_BACKSPACE)
				input_string = input_string.substr(0, input_string.size() - 1);

			if(event.key.keysym.sym == SDLK_SPACE)
				input_string += ' ';

			if(std::isalpha(event.key.keysym.sym) || std::isgraph(event.key.keysym.sym)){

				if(event.key.keysym.mod & KMOD_SHIFT)
					input_string += translate(event.key.keysym.sym);
				else
					input_string += event.key.keysym.sym;
			}
		}
		
		if(event.type == SDL_KEYUP){
			Released[event.key.keysym.scancode] = true;
			Held[event.key.keysym.scancode] = false;
		}
	}
}

bool input::key_Pressed(int key){
	return Pressed[key];
}

bool input::key_Released(int key){
	return Released[key];
}

bool input::key_Held(int key){
	return Held[key];
}

int input::mouse_PositionX(){
	int mx;
	SDL_GetMouseState(&mx, NULL);
	return mx;
}

int input::mouse_PositionY(){
	int my;
	SDL_GetMouseState(NULL, &my);
	return my;
}

void input::reset_string(){
	input_string = "";
}

std::string input::get_string(){
	return input_string;
}

void input::set_string(std::string set){
	input_string = set;
}