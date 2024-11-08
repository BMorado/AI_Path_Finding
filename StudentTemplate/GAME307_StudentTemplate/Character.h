#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>

#include "Scene.h"
#include "KinematicBody.h"
#include "StaticBody.h"

using namespace std;

class Character
{
private:
	class KinematicBody* body;
	StaticBody* body_;
	class Scene* scene;

public:
	Character()
	{
		body = NULL;
		scene = NULL;
	};

	~Character() {};

	bool OnCreate(Scene* scene_);
	void OnDestroy();
	bool setTextureWith(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	StaticBody* getStaticBody() { return body_; }
	void render(float scale = 1.0f) const;

};

#endif

