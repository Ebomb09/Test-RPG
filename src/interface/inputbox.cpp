#include <iostream>
#include "game.h"
#include "interface/inputbox.h"

void inputbox::update(game* Game){

	std::cout << "Input a string! ";
	output = "TEST STRING";
	Game->load_Return();
}

void inputbox::draw(game* Game){

}