#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

GameObject* player;
GameObject* enemy;

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


	player = new GameObject("assets/wizard_32x32.png", renderer, 0, 0, 32, 32, scale);
	enemy = new GameObject("assets/draziw_32x32.png", renderer, 50, 50, 32, 32, scale);

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
	player->Update();
	enemy->Update();

	lastUpdateEnd = SDL_GetTicks();
}
void Game::render()
{
	SDL_RenderClear(renderer);
	// draw stuff to render
	player->Render();
	enemy->Render();

	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
