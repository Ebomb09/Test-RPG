#include "game.h"
#include "interface/mainmenu.h"

int main(int argc, char* argv[]){

	game RPGtest;
	RPGtest.init();
	RPGtest.load_MainMenu();

	return 0;
}