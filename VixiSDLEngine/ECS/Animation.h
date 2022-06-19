#pragma once
#include <vector>
struct Animation
{
	int index;
	int frames;
	int speed;

	Animation() {}
	Animation(int i, int nFrames, int nSpeed)
	{
		index = i;
		frames = nFrames;
		speed = nSpeed;
	}

};