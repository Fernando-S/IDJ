#pragma once
#include "SDL_mixer.h"
#include <string>

class Music {
public:
	Music();
	Music(const char* file);
	void Play(int times = -1);
	void Stop(int msToStop = 1500);
	void Open(const char* file);
	bool IsOpen();
	~Music();

private:
	Mix_Music* music;
};
