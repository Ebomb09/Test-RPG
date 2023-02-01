#include <iostream>
#include <string>
#include "game.h"
#include "interface/mainmenu.h"

mainmenu::mainmenu(){

}

void mainmenu::update(){
	std::cout << "I want a string\n";
	Game->load_InputBox(&get_string);
}

void mainmenu::draw(){

}

void mainmenu::get_string(interface* it, void **args){
	std::cout << "String entered " << *(std::string*)args[0] << '\n';
	it->Game->game_loop = false;
}