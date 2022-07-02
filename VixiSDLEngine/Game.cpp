#include "Game.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "Vector2D.h"
#include "Components.h"
#include "Collision.h"



SDL_Renderer* Game::renderer = nullptr;
Manager manager;

float Game::drawScale;
float Game::delta;
Uint8 Game::tileSize;
bool Game::isRunning = false;
//SDL_Rect* Game::camera;
TileMap* map;


SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

auto& camera(manager.addEntity());
auto& player(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
};

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
	drawScale = 1.0f;
	tileSize = 32;

	camera.addComponent<CameraComponent>();
	camera.getComponent<CameraComponent>().UpdateScreenSize(width * tileSize, height * tileSize);

	map = new TileMap(25, 20, 1); 
	camera.getComponent<CameraComponent>().AdjustToMap(map->width * tileSize, map->height * tileSize);

	

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer initialized" << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
		std::cout << "game failed to initialized, error!!!" << std::endl;
	}

	map->LoadTileMap("assets/map.map",25,20,"assets/terrain_ss.png");

	player.addComponent<TransformComponent>(120,100,32,32,1);
	player.addComponent<SpriteComponent>("assets/wizard_animationSet.png",true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
	player.getComponent<SpriteComponent>().AddCamera(&camera.getComponent<CameraComponent>());
	camera.getComponent<CameraComponent>().setTarget(&player);

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

	/*float dt = 1.0f / 60.0f;
	if (delta > dt)
	{
		delta = dt;
	}
	*/

	// update
	manager.Refresh();
	manager.Update();
	//camera->Update();

	for (auto cc : colliders)
	{
		if (Collisons::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->tag != "player")
		{
			player.getComponent<TransformComponent>().velocity *= -1;
		}
	}
	
}

auto& gTiles(manager.getGroup(groupMap));
auto& gPlayers = manager.getGroup(groupPlayers);


void Game::Render()
{
	SDL_RenderClear(renderer);
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

void Game::AddTileToTileMap(int srcX, int srcY, int xpos, int ypos, const char* path, int scale)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, path, scale);
	tile.getComponent<TileComponent>().AddCamera(&camera.getComponent<CameraComponent>());
	tile.addGroup(groupMap);
	
}
