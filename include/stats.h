#ifndef GAME_STATS_H
#define GAME_STATS_H

#include <cstddef>

struct statistics{

	enum name{
		HP				= 0,
		HEALTH_POINTS	= HP,
		STR 			= 1,
		STRENGTH		= STR,
		MAG				= 2,
		MAGIC			= MAG,
		VIT				= 3,
		VITALITY		= VIT,
		SPR				= 4,
		SPIRIT			= SPR,
		SPD				= 5,
		SPEED			= SPD
	};

	int hp  = 0;
	int str = 0;
	int mag = 0;
	int vit = 0;
	int spr = 0;
	int spd = 0;

	int* get_stat(name stat);
};

#endif