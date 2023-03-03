#ifndef GAME_DEFINES_H
#define GAME_DEFINES_H

struct characters{
	enum{
		wizardcat,
		dragonknight,
		fireguy,
		total,
		maxpartysize = 4
	};
};

struct enemies{
	enum{
		slime,
		total
	};
};

struct moves{
	enum{
		attack,
		item,
		fire,
		thunder,
		ice,
		total
	};
};

#endif