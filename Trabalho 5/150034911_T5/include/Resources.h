#pragma once

#ifndef RESOURCES_H
#define RESOURCES_H

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <iostream>
#include <unordered_map>
//#include "SDL_mixer.h"							// Comentar e usar SDL_include.h para enviar
//#include "SDL_image.h"							// Comentar e usar SDL_include.h para enviar


class Resources{
public:
		static SDL_Texture *GetImage(std::string file);
		static void ClearImages();
		static Mix_Music *GetMusic(std::string file);
		static void ClearMusics();
		static Mix_Chunk *GetSound(std::string file);
		static void ClearSounds();

private:
		static std::unordered_map<std::string, SDL_Texture*> imageTable;
		static std::unordered_map<std::string, Mix_Music*> musicTable;
		static std::unordered_map<std::string, Mix_Chunk*>soundTable;

};

#endif	//RESOURCES_H