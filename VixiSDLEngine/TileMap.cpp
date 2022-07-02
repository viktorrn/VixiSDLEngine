#include "TileMap.h"
#include "Game.h"
#include "TextureManager.h"
#include <fstream>



TileMap::TileMap(int mWidth, int mHeight, int scale)
{
	this->scale = scale;
	this->width = mWidth* scale;
	this->height = mHeight* scale;
}

TileMap::~TileMap()
{

}

void TileMap::LoadTileMap(std::string path, int sizeX, int sizeY, const char* map_ss)
{
	char c;
	std::fstream mapFile;
	mapFile.open(path);
	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) 
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			srcY = atoi(&c) * Game::tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * Game::tileSize;
			Game::AddTileToTileMap(srcX, srcY, x * Game::tileSize * scale, y * Game::tileSize * scale, map_ss, scale);
			mapFile.ignore();
		}
	}

	mapFile.close();
}

