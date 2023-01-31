#include "game.h"

game::game(){

}

game::~game(){
	
}

void game::init(){

}

void game::load_MainMenu(){
	active_interfaces.clear();
	active_interfaces.push_front(&MainMenu);
}

void game::run(){

}