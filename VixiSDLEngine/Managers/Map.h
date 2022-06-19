#pragma once
#include "../libDependecies.h"

class Map
{
public:
	
	Map(int mWidth, int mHeight);
	~Map();

	static void LoadMap(std::string path, int sizeX, int sizeY);

private:


};

