#include "input.h"

input::input(){
	quit = false;
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