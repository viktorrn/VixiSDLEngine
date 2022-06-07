#pragma once
#include "libDependecies.h";

class Game
{
public:
	Game( );
	~Game( );
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running(){ return isRunning; }

private:
	float delta = 1;
	float scale = 2;
	Uint32 lastUpdateEnd = 0;
	int cnt = 0;
	bool isRunning;
	SDL_Window * window;
	SDL_Renderer *renderer;


};

