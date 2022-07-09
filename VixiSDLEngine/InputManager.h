#pragma once
#include "libDependecies.h"
#include <map>
#include "Vector2D.h"

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;
	void Init();
	void Update();
	const int GetMouseX()
	{
		return mousePos->x;
	}
	const int GetMouseY()
	{
		return mousePos->y;
	}
	const int GetPrevMouseX()
	{
		return prevMousePos->x;
	}
	const int GetPrevMouseY()
	{
		return prevMousePos->y;
	}
	bool GetInputState(const std::string str)
	{
		return inputMap[str];
	}
	
private:
	Vector2D* prevMousePos;
	Vector2D* mousePos;
	std::map<std::string, bool> inputMap;
};

