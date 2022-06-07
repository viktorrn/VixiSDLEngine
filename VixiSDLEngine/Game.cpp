#include "Game.h"
#include "TextureManager.h"

SDL_Texture* texture;
SDL_Rect srcR, destR;

Game::Game() 
{

}
Game::~Game()
{

}
void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem init" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
		if (window) 
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 2555, 255, 255);
			std::cout << "Renderer initialized" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
		std::cout << "game failed to initialized, error!!!" << std::endl;
	}


	texture = TextureManager::LoadTexture("assets/wizard_32x32.png", renderer);

}
void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	};
	
}
void Game::update()
{
	delta = (SDL_GetTicks() - lastUpdateEnd) / 1000.0f;
	
	// update
	destR.h = 32 *scale;
	destR.w = 32 *scale;
	std::cout << delta << std::endl;
	lastUpdateEnd = SDL_GetTicks();
}
void Game::render()
{
	SDL_RenderClear(renderer);
	// draw stuff to render
	SDL_RenderCopy(renderer, texture, NULL, &destR);

	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
