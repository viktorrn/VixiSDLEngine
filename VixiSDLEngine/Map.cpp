#include "Map.h"
#include "TextureManager.h"

static int w = 20;
static int h = 12;

int Map::width = 1;
int Map::height = 1;

Uint8 lvl1[20 * 12] =
{
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
	 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ,
};

Map::Map(int mWidth, int mHeight)
{
	
	Uint8* m = new Uint8[mWidth * mHeight]();

	width = mWidth;
	height = mHeight;

	srcRect.x = srcRect.y = destRect.x = destRect.y = 0;
	srcRect.w = srcRect.h = destRect.w = destRect.h = 32 * Game::drawScale;

	dirt = TextureManager::LoadTexture("assets/dirt.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	water = TextureManager::LoadTexture("assets/water.png");
	
	LoadMap(lvl1);
	

	
}

Map::~Map()
{
	SDL_DestroyTexture(dirt);
	SDL_DestroyTexture(grass);
	SDL_DestroyTexture(water);
}

void Map::LoadMap(Uint8* arr)
{
	map = new Uint8[width*height]();

	for (int index = 0; index < getMapSize(); index++)
	{
		map[index] = arr[index];
	}
}

void Map::DrawMap()
{
	int type = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			
			type = map[ y*width + x ];

			destRect.x = x*32*Game::drawScale;
			destRect.y = y*32*Game::drawScale;

			switch (type)
			{
			case 0:
				TextureManager::Draw(grass, srcRect, destRect);
				break;
			case 1:
				TextureManager::Draw(water, srcRect, destRect);
				break;
			case 2:
				TextureManager::Draw(dirt, srcRect, destRect);
				break;
			default:
				break;
			}
		}
	}

}
