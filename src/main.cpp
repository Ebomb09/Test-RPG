#include <iostream>
#include "game.h"
#include "interface/mainmenu.h"

int main(int argc, char* argv[]){

	std::cout << "Creating a game object\n";
	game RPGtest;

	std::cout << "Loading the main menu pointer\n";
	RPGtest.load_MainMenu();

	std::cout << "Starting game loop\n";
	RPGtest.run();

	return 0;
}