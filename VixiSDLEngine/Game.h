#pragma once
#include "libDependecies.h";

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

	static float drawScale;
	static Uint8 tileSize;
	static SDL_Renderer* renderer;
	static SDL_Event event;
private:

	float delta = 1;
	Uint32 lastUpdateEnd = 0;
	int cnt = 0;
	bool isRunning;
	SDL_Window * window;


};

