#ifndef AUDIO_GAME_H
#define AUDIO_GAME_H

#include <string>

#include "SDL2/SDL.h"
#include "SDL_mixer.h"

#include "page.h"

class audio{

protected:

	page<Mix_Chunk*, std::string, 8> sounds;
	page<Mix_Music*, std::string, 4> music;

	Mix_Music* load_Music(std::string audio);
	Mix_Chunk* load_Sound(std::string audio);

	bool init();

public:
	~audio();

	bool play_Music(std::string audio);
	bool play_Sound(std::string audio);
};

#endif