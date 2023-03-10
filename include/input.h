#ifndef INPUT_GAME_H
#define INPUT_GAME_H

#include <string>
#include <map>
#include "SDL2/SDL.h"

class input{

protected:
	bool quit;

	std::map<const int, bool> Pressed;
	std::map<const int, bool> Released;
	std::map<const int, bool> Held;

	std::string input_string;

	bool init();
	void poll();
	void refresh(std::map<const int, bool>& map);

public:
	input();
	~input();

	bool key_Pressed(int key);
	bool key_Released(int key);
	bool key_Held(int key);

	int mouse_PositionX();
	int mouse_PositionY(); 

	void reset_string();
	std::string get_string();
	void set_string(std::string set);
};

#endif