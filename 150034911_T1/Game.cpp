#include "Game.h"
//#include "SDL_image.h"
//#include "SDL_mixer.h"
#include "SDL_include.h"
#include "State.h"
#include <iostream>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER


Game* Game::instance = nullptr;

Game::~Game() {
	/* Fecha tudo */
	delete state;
	Mix_Quit();
	Mix_CloseAudio();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Run() {
	while (!state->QuitRequested()) {
		state->Update(1);					// TODO - descobrir que valor mandar
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);						// tempo em ms para algo proximo de 30 fps
	}
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}


State& Game::GetState(){
	return *state;
}

Game& Game::GetInstance() {	
	if (instance != nullptr)
		return *instance;										// retorna a instancia se ja existir uma
	else {
		instance = new Game("Joguinho maneiro", 1024, 600);		// instancia um novo jogo
		return *instance;										// retorna a nova instancia instancia
	}
}

Game::Game(const char*, int, int) {
	// Checa se ja existe uma instancia	
	if (instance != nullptr) {
		std::cerr << "\n\n ERROR: Can't instantiate the game. Game already running \n\n" << std::endl;
		exit(1);
	}

	instance = this;

	// Inicializando as bibliotecas 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		std::cerr << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}

	if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)) {
		std::cerr << "\n\n ERROR: SDL_Mixer couldn't be initialized \n\n" << std::endl;
		exit(1);
	}

	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		std::cerr << "\n\n ERROR: SDL_Image couldn't be initialized \n\n" << std::endl;
		exit(1);
	}
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {		// MIX_DEFAULT_ para todos e 1024 no hcunksize
		std::cerr << "\n\n ERROR: Mix_OpenAudio returned ERROR \n\n" << Mix_GetError() << std::endl;
		exit(1);
	}

	if (Mix_AllocateChannels(32) != 32) {				// 32 canais de audio
		std::cerr << "\n\n ERROR: impossible to allocate 32 audios channels \n\n" << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow("Fernando Sobral Nobrega 15/0034911", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 600, 0);		// title, pos x, pos y, width, height, fullscreen
	if (!window) {
		std::cerr << "\n\n ERROR: impossible to create window \n\n" << std::endl;
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);		// -1 = SLD escolhe o melhor renderizador e ACCELERATED requisita OpenGL ou Direct 3D
	if (!renderer) {
		std::cerr << "\n\n ERROR: impossible to create render \n\n" << std::endl;
		exit(1);
	}

	state = new State();
}

