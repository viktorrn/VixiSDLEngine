#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "Vector2D.h"
#include <vector>
#include "Components.h"
#include "Collision.h"
#include "CellTileMap.h"


SDL_Renderer* Game::renderer = nullptr;
Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);
InputManager* Game::inputs = new InputManager();

float Game::drawScale;
float Game::delta;
Uint8 Game::tileSize;
bool Game::isRunning = false;
TileMap* map;
SDL_Event Game::event;
CellTileMap* cells;

std::vector<ColliderComponent*> Game::colliders;


auto& camera(manager.addEntity());;


Game::Game() 
{
}

Game::~Game()
{

}

void Game::Init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	srand((int)time(0));
	// some required setting values
	drawScale = 1.0f;
	tileSize = 16;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystem init" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width*tileSize* drawScale, height * tileSize* drawScale, flags);
		
		if (window) 
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer initialized" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
		std::cout << "game failed to initialized, error!!!" << std::endl;
	}

	if (!isRunning) return;

	// init data

	inputs->Init();

	cells = new CellTileMap();
	assets->AddTexture("tile", "assets/tiles_ss.png");

	cells->AdjustCellMap(width, height);
	cells->GenerateCellMap();
	//cells->LoadCellMap("assets/Map_32x32.map", 32, 32);

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
	
	Uint32 now = SDL_GetTicks();
	Game::delta = (now - lastUpdateEnd) / 1000.0f;
	lastUpdateEnd = now;

	float dt = 1.0f / 60.0f;

	/*
	if (delta > dt)
		{	
			delta = dt;
		}

	*/

	// update

	inputs->Update();
	cells->Update();

	manager.Refresh();
	manager.Update();

	//camera->Update();
	
}

auto& gTiles(manager.getGroup(Game::groupMap));
auto& gPlayers = manager.getGroup(Game::groupPlayers);


void Game::Render()
{
	SDL_RenderClear(renderer);

	cells->Draw();

	for (auto& t : gTiles)
	{
		t->Draw();
	}

	for(auto& p : gPlayers)
	{
		p->Draw();
	}
	
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}

void Game::AddTileToTileMap(int srcX, int srcY, int xpos, int ypos, const std::string ID, int scale)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, ID, scale);
	tile.getComponent<TileComponent>().AddCamera(&camera.getComponent<CameraComponent>());
	tile.addGroup(groupMap);
	
}

size_t Game::GetRandom(size_t max)
{
	return rand() % (max + 1);
}
