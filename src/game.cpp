#include <iostream>
#include "game.h"

game::game(){
	game_loop = true;
	init();
}

game::~game(){
	
}

void game::init(){
	MainMenu.Game = this;
	InputBox.Game = this;
}

void game::load_Return(){

	if(!active_interfaces.empty()){
		interface* caller = active_interfaces.front();
		active_interfaces.pop_front();
		interface* handler = active_interfaces.front();

		if(caller->callback && handler)
			caller->callback(handler, caller->args);

		caller->callback = NULL;
	}
}

void game::load_MainMenu(){
	active_interfaces.clear();
	active_interfaces.push_front(&MainMenu);
}

void game::load_InputBox(callbackFn callback){
	InputBox.callback = callback;
	active_interfaces.push_front(&InputBox);
}

void game::run(){

	while(game_loop){

		// Only update logic for the top most interface
		if(!active_interfaces.empty())
			active_interfaces.front()->update();

		// Draw from bottom to top
		for(std::list<interface*>::reverse_iterator it = active_interfaces.rbegin(); it != active_interfaces.rend(); it ++)
			(*it)->draw();
	}
}