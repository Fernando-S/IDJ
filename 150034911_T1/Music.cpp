#include "Music.h"
#include <string>
#include <iostream>

Music::Music() {
	music = nullptr;
};

Music::Music(const char* file) {
	music = nullptr;
	Open(file);
};

void Music::Play(int times) {
	if (music) 
		Mix_PlayMusic(music, times);				// se times for -1, a musica repete infinitamente. Se for 0, a musica nao toca
	else
		std::cerr << "ERROR: music is null" << std::endl;
};

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);						// tenpo em ms
};

void Music::Open(const char* file) {
	music = Mix_LoadMUS(file);
	if (!music)
		std::cerr << "ERROR: impossible to load music" << std::endl;
};

bool Music::IsOpen() {
	if (music != nullptr)
		return true;
	else
		return false;
};

Music::~Music(){
	if (music) {
		Stop(1500);									//1500 ms
		Mix_FreeMusic(music);
	}
};