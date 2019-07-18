#pragma once
#include "Texture2D.h"
class Animation
{
public:
	Animation();
	~Animation();

	int maxFrames;
	bool oscillate;

	void OnAnimate();

	int setFrameRate(int newFrameRate) { return frameRate = newFrameRate; }
	int setCurrentFrame(int newFrame) { return currentFrame = newFrame; }
	int getCurrentFrame() { return currentFrame + startIndex; }

	void addDelay(int delayTime, int animationRunTime);

	int setAnimationAtlasPosition(int X, int Y) { return x = X, y = Y; }
	int getX() { return x; }
	int getY() { return y; }

	std::vector<Texture2D> Sprites;
	std::vector<Texture2D> SpriteNormals;

	//! Set at which point in the sprite sheet the animation starts at
	int setStartIndex(int newStart) { return startIndex = newStart; }
	bool runOnce = false;
private:
	int startIndex = 0;
	int endIndex = 0;

	int currentFrame;
	int frameInc;
	int frameRate;
	long oldTime;
	int startTime;

	int x;
	int y;

};

