#ifndef GAME_CHARACTERS_H
#define GAME_CHARACTERS_H

#include <string>

struct character{
	std::string asset;
	std::string name;
	int str;
	int mag;
	int def;
	int spr;
	int spd;
};

#endif 