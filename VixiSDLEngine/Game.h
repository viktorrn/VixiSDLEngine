#pragma once
#include "libDependecies.h";
#include "AssetManager.h"

class ColliderComponent;
class AssetManager;

class Game
{

public:

	Game( );
	~Game( );
	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool Running() { return isRunning; };
	static void AddTileToTileMap(int srcX, int srcY, int xpos, int ypos, const std::string ID, int scale);

	static float drawScale;
	static float delta;
	static Uint8 tileSize;
	
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	
	static bool isRunning;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
	};

private:

	
	Uint64 lastUpdateEnd = 0;
	int cnt = 0;
	
	SDL_Window * window;


};

