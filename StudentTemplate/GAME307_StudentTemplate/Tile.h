#pragma once

#include "Scene.h"

class Tile
{
private:
	float width, height;
	Uint8 r = 0, g=255, b=0, a=255;
	Vec3 pos;
	Scene* scene;
	

public:
	Tile(Vec3 pos_, float width_, float height_, Scene* scene_);
	void SetRGBA(Uint8 r_, Uint8 g_, Uint8 b_, Uint8 a_)
	{
		r = r_;
		b = b_;
		g = g_;
		a = a_;
	}
	bool valid = true;
	virtual ~Tile();
	void Render();
};

