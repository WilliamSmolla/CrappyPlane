#pragma once
#include "pch.h"
#include "maths/Maths.h"
#include "graphics/Texture.h"
#include "utils/Timer.h"

struct Tag
{
	std::string tag;
	unsigned int layer;
};

struct Layer
{
	int layer;
};

struct Transform
{
	Vec2 position;
};

struct SpriteRenderer
{
	Texture sprite;
	bool isAnimated = false;
	int timeBetweenFrames;
	int numberOfFrames;
	Timer timer;
	bool isLooping = false;
};

struct Collider
{
	int test = 0;
};

struct Movement
{
	Vec2 velocity = Vec2(0, 0);
	Vec2 acceleration = Vec2(0, 0);
};



