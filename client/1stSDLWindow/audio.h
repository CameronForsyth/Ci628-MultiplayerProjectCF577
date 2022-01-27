#pragma once
//#define AUDIO_H

#include "Game.h"
#include "SDL.h"
#include "SDL_mixer.h"

class audio
{
public: 
	audio(SDL_items* source);
	~audio();
	void load(const char* filename);

	void init_audio();
	void play_sound();
	void destroy();
private:

	Mix_Chunk* sound;
	SDL_items* src;
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 wavBuffer;
	SDL_AudioDeviceID deviceId;
};

