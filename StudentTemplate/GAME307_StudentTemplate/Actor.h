#pragma once
#include "Scene.h"
class Actor
{
private:
	//Vec3 pos;
	float scale;
	Scene* scene;
	SDL_Texture* texture;
	float orientation;
public:
	Vec3 pos;
	Actor(Vec3 pos_,float scale_, float orientation_,Scene* scene_,SDL_Texture* texture_) :pos(pos_) ,scale(scale_),orientation(orientation_), scene(scene_), texture(texture_) {}

	void Update();
	void SetPos(Vec3 pos_);
	void Render();
};

