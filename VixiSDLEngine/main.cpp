#include "libDependecies.h";
#include "Game.h"

using namespace std;

Game *game = nullptr;

int main(int argc, char *argv[])
{
	game = new Game();
	const int FPS = 250;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 20*2, 12*2, false);

	while(game->Running())
	{
		frameStart = SDL_GetTicks();
		//cout << frameStart << endl;
		//cout << SDL_GetTicks();
		//cout << SDL_GetPerformanceFrequency() << endl;
		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	game->Clean();

	return 0;
}