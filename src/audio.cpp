#include "audio.h"
#include <iostream>

audio::~audio(){

	for(int i = 0; i < music.count(); i ++)
		Mix_FreeMusic(music[i]);

	for(int i = 0; i < sounds.count(); i ++)
		Mix_FreeChunk(sounds[i]);

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool audio::init(){
	SDL_InitSubSystem(SDL_INIT_AUDIO);

	if(Mix_Init(MIX_INIT_MP3) == 0)
		return false;

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		return false;

	return true;
}

Mix_Music* audio::load_Music(std::string audio){

	Mix_Music* song = music.find(audio);

	if(!song){
		song = Mix_LoadMUS(audio.c_str());

		if(song){
			Mix_Music* old = music.replace(song, audio);
			Mix_FreeMusic(old);
		}
	}
	return song;
}

Mix_Chunk* audio::load_Sound(std::string audio){

	Mix_Chunk* sound = sounds.find(audio);

	if(!sound){
		sound = Mix_LoadWAV(audio.c_str());

		if(sound){
			Mix_Chunk* old = sounds.replace(sound, audio);
			Mix_FreeChunk(old);
		}
	}
	return sound;
}

bool audio::play_Music(std::string audio){

	Mix_Music* music = load_Music(audio);

	return (Mix_PlayMusic(music, 1) == 0);
}

bool audio::play_Sound(std::string audio){
	
	Mix_Chunk* sound = load_Sound(audio);

	return (Mix_PlayChannel(-1, sound, 1) > 0);
}