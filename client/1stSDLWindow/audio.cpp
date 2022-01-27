#include "audio.h"

audio::audio(SDL_items* source)
{
    src = source;
}

audio::~audio()
{
}

void audio::load(const char* filename)
{
}

void audio::init_audio()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        return;
    }

    // all good to go
    sound = Mix_LoadWAV(src->_waveFileNames[0]);
    if (sound == nullptr) {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }
    else {
        std::cout << "Sound effect loaded" << std::endl;
    }
}

void audio::play_sound()
{
    if (Mix_PlayChannel(-1, sound, 0) == -1) {
        printf("Error playing sound. Mix_PlayChannel: %s\n", Mix_GetError());
    }
}

void audio::destroy()
{
    Mix_FreeChunk(sound);
    sound = nullptr;

    Mix_CloseAudio();
}
