#include <iostream>
#include "game.h"
#include "interface/inputbox.h"

void inputbox::update(){

	std::cout << "Input a string! ";
	output = "TEST STRING";
	Game->load_Return();
}

void inputbox::draw(){

}