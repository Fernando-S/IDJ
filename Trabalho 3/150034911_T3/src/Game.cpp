#include "Game.h"


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
		return *instance;		// retorna a instancia se ja existir uma
	else {
		instance = new Game("Fernando Sobral Nobrega 15/0034911", 1024, 600);		// instancia um novo jogo
		return *instance;		// retorna a nova instancia instancia
	}
}

Game::Game(const char* title, int width, int height) {
	// Checa se ja existe uma instancia	
	if (instance != nullptr) {
		std::cerr << "\n\n ERROR: Can't instantiate the game. Game already running \n\n" << std::endl;
		exit(1);
	}

	instance = this;

	// Inicializando as bibliotecas 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		std::cerr << " SDL_Init ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}

	if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)) {
		std::cerr << " ERROR: SDL_Mixer couldn't be initialized " << std::endl;
		exit(1);						// Erro de versao. Monitor Francisco sugeriu para comentar
	}

	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		std::cerr << " ERROR: SDL_Image couldn't be initialized " << std::endl;
		exit(1);
	}
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {		// MIX_DEFAULT_ para todos e 1024 no hcunksize
		std::cerr << " ERROR: Mix_OpenAudio returned ERROR " << Mix_GetError() << std::endl;
		exit(1);
	}

	if (Mix_AllocateChannels(32) != 32) {				// 32 canais de audio
		std::cerr << " ERROR: impossible to allocate 32 audios channels " << std::endl;
		exit(1);
	}
	
	// Cria uma nova janela
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);		// title, pos x, pos y, width, height, fullscreen
	if (!window) {
		std::cerr << " ERROR: impossible to create window " << std::endl;
		exit(1);
	}

	// Cria um novo renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);		// -1 = SLD escolhe o melhor renderizador e ACCELERATED requisita OpenGL ou Direct 3D
	if (!renderer) {
		std::cerr << " ERROR: impossible to create render " << std::endl;
		exit(1);
	}

	state = new State();
}