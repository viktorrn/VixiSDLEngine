#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "Vector2D.h"
#include "ECS/Components.h"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
float Game::drawScale = 1.0f;
Uint8 Game::tileSize = 1;

Manager manager;
SDL_Event Game::event;
auto& player(manager.addEntity());

Game::Game() 
{
}
Game::~Game()
{

}
void Game::Init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	
	// some required setting values
	drawScale = 2.0f;
	tileSize = 32;


	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem init" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width*tileSize, height * tileSize, flags);
		
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

	map = new Map(20,12);

	player.addComponent<TransformComponent>(50,100);
	player.addComponent<SpriteComponent>("assets/wizard_32x32.png");
	

}
void Game::HandleEvents()
{


	SDL_PollEvent(&event);
	
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	};
	
}
void Game::Update()
{
	delta = (SDL_GetTicks() - lastUpdateEnd) / 1000.0f;
	
	// update
	manager.Refresh();
	manager.Update();
	player.getComponent<TransformComponent>().position += Vector2D(2, 0);
	if (player.getComponent<TransformComponent>().position.x > 100)
	{
		player.getComponent<SpriteComponent>().SetTexture("assets/draziw_32x32.png");
	}

	lastUpdateEnd = SDL_GetTicks();
}
void Game::Render()
{
	SDL_RenderClear(renderer);
	// draw stuff to render
	map->DrawMap();
	manager.Draw();

	SDL_RenderPresent(renderer);
}
void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
