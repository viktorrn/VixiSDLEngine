#include "libDependecies.h";
#include "Game.h"

using namespace std;

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 20*2, 12*2, false);

	while(game->Running())
	{
		frameStart = SDL_GetPerformanceCounter();


		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetPerformanceCounter() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->Clean();

	return 0;
}