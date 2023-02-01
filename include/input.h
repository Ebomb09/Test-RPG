#ifndef INPUT_GAME_H
#define INPUT_GAME_H

#include <map>
#include "SDL2/SDL.h"

class input{

protected:
	bool quit;

	std::map<const int, bool> Pressed;
	std::map<const int, bool> Released;
	std::map<const int, bool> Held;

	bool init();
	void poll();
	void refresh(std::map<const int, bool>& map);

public:
	input();
	~input();

	bool key_Pressed(int key);
	bool key_Released(int key);
	bool key_Held(int key);
};

#endif