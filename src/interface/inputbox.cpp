#include <iostream>
#include "game.h"
#include "interface/inputbox.h"

inputbox::inputbox(){
	args = new void*[1];
	args[0] = &output;
}

void inputbox::update(){

	std::cout << "Input a string! ";
	std::cin >> output;

	Game->load_Return();
}

void inputbox::draw(){

}