#pragma once
#include "libDependecies.h"


class TileMap
{
public:

	int drawWidth;
	int drawHeight;
	int scale;

	TileMap(int mWidth, int mHeight, int scale);
	~TileMap();

	void LoadTileMap(std::string path, int sizeX, int sizeY, const std::string ID);

private:


};

