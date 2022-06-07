#include "libDependecies.h";
#include "Game.h"

using namespace std;

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();
	const int FPS = 60;
	const float frameDelay = 1000.0f / FPS;

	Uint32 frameStart;
	int frameTime;

	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, false);

	while(game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->clean();

	return 0;
}