#include "Map.h"
#include "../Game.h"
#include "TextureManager.h"
#include <fstream>



Map::Map(int mWidth, int mHeight)
{

}

Map::~Map()
{

}

void Map::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++) 
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			Game::AddTile(atoi(&tile), x * Game::tileSize, y * Game::tileSize);
			mapFile.ignore();
		}
	}

	mapFile.close();
}

