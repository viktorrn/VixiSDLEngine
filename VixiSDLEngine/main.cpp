#include "libDependecies.h";
#include "Game.h"

using namespace std;

Game *game = nullptr;
//enum class CellProperties
//{
//	NONE = 0b00000000,
//	MOVE_DOWN = 0b00000001,
//	MOVE_DOWN_SIDE = 0b00000010,
//	MOVE_SIDE = 0b00000100,
//};
//
//inline int operator | (CellProperties a, CellProperties b)
//{
//	return (static_cast<int>(a) | static_cast<int>(b));
//};



int main(int argc, char *argv[])
{
	game = new Game();
	const int FPS = 60;//24;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;




	//cout << static_cast<bool>(3 & 1) << std::endl;

	game->Init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 128, 64, false);

	while (game->Running())
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