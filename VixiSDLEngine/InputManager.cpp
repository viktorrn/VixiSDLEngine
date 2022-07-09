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
			inputMap["0"] = false;
			break;
		case SDLK_1:
			inputMap["1"] = false;
			break;
		case SDLK_2:
			inputMap["2"] = false;
			break;
		case SDLK_3:
			inputMap["3"] = false;
			break;
		}
	}

	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_0:
			inputMap["0"] = true;
			inputMap["1"] = false;
			inputMap["2"] = false;
			inputMap["3"] = false;
			break;

		case SDLK_1:
			inputMap["0"] = false;
			inputMap["1"] = true;
			inputMap["2"] = false;
			inputMap["3"] = false;
			break;

		case SDLK_2:
			inputMap["0"] = false;
			inputMap["1"] = false;
			inputMap["2"] = true;
			inputMap["3"] = false;
			break;

		case SDLK_3:
			inputMap["0"] = false;
			inputMap["1"] = false;
			inputMap["2"] = false;
			inputMap["3"] = true;
			break;
		}
	}
}

