#pragma once
#include "libDependecies.h"

class Map
{
public:
	
	Map(int mWidth, int mHeight);
	~Map();

	void LoadMap(Uint8* arr);
	void DrawMap( );
	int getWidth() { return width; };
	int getHeight() { return height; };
	int getMapSize() { return width * height; };
	

	static int width;
	static int height;

private:

	SDL_Rect srcRect, destRect;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	Uint8* map;

};

