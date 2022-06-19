#pragma once
#include "libDependecies.h";

class ColliderComponent;

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
	static void AddTile(int id, int x, int y);

	static float drawScale;
	static float delta;
	static Uint8 tileSize;
	
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:

	
	Uint64 lastUpdateEnd = 0;
	int cnt = 0;
	bool isRunning;
	SDL_Window * window;


};

