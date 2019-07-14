#include "Resources.h"
#include "Game.h"

#include "Resources.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;


SDL_Texture * Resources::GetImage(std::string file) {	
	
	auto search = imageTable.find(file);
	if (search != imageTable.end())				// continua a procurar a imagem se ainda nao esta no final do vetor
		return search->second;
	else {										// tenta carregar a imagem se chegou ao final do vetor
		auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if (!texture) {
			std::cerr << " IMG_LoadTexture returned ERROR: " << SDL_GetError() << std::endl;
			exit(1);
		}
		imageTable[file] = texture;
		return texture;
	}
}

void Resources::ClearImages() {
		for (auto it : imageTable){
			SDL_DestroyTexture(it.second);				// destroi cada imagem
		}
		imageTable.clear();								// libera espaco da memoria
}

Mix_Music * Resources::GetMusic(std::string file) {
	
	auto search = musicTable.find(file);
	if (search != musicTable.end())				// continua a procurar a msuica se ainda nao esta no final do vetor
		return search->second;
	else {										// tenta carregar a musica se chegou ao final do vetor
		auto music = Mix_LoadMUS(file.c_str());
		if (!music) {
			std::cerr << " Mix_LoadMUS returned ERROR: " << Mix_GetError() << std::endl;
			exit(1);
		}
		musicTable[file] = music;
		return music;
	}
}

void Resources::ClearMusics() {
		for (auto it : musicTable) {
			Mix_FreeMusic(it.second);					// destroi cada musica
		}
		musicTable.clear();								// libera espaco da memoria
}

Mix_Chunk* Resources::GetSound(std::string file) {
	
	auto search = soundTable.find(file);
	if (search != soundTable.end())				// continua a procurar a msuica se ainda nao esta no final do vetor
		return search->second;
	else {										// tenta carregar o som se chegou ao final do vetor
		auto sound = Mix_LoadWAV(file.c_str());
		if (!sound) {
			std::cerr << " IMG_LoadTexture returned ERROR: " << Mix_GetError() << std::endl;
			exit(1);
		}
		soundTable[file] = sound;
		return sound;
	}
}

void Resources::ClearSounds() {
		for (auto it : soundTable) {
			Mix_FreeChunk(it.second);					// destroi cada som
		}
		soundTable.clear();								// libera espaco da memoria
}