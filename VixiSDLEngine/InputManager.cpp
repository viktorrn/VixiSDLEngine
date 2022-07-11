#include "InputManager.h"
#include "SDL.h"

void InputManager::Init()
{

	mousePos = new Vector2D();
	inputMap.emplace("0", false);
	inputMap.emplace("1", false);
	inputMap.emplace("2", false);
	inputMap.emplace("3", false);
	inputMap.emplace("mbl", false);

}

void InputManager::Update()
{
	prevMousePos = mousePos;
	SDL_PumpEvents();
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	
	mousePos->x = x;
	mousePos->y = y;
	inputMap["mbl"] = (buttons & SDL_BUTTON_LEFT);

	//std::cout << (*mousePos)  << std::endl;
	//std::cout << inputMap["mbl"] << std::endl;

	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_0:
			
			break;
		case SDLK_1:
			
			break;
		case SDLK_2:
		
			break;
		case SDLK_3:
			
			break;
		}
	}

	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_0:
			inputInt = 0;
			break;

		case SDLK_1:
			inputInt = 1;
			break;

		case SDLK_2:
			inputInt = 2;
			break;

		case SDLK_3:
			inputInt = 3;
			break;
		case SDLK_4:
			inputInt = 4;
			break;
		}
	}
}

