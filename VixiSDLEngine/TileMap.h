#pragma once
#include "libDependecies.h"

class TileMap
{
public:

	int width;
	int height;
	int scale;

	TileMap(int mWidth, int mHeight, int scale);
	~TileMap();

	void LoadTileMap(std::string path, int sizeX, int sizeY, const char* map_ss);

private:


};

