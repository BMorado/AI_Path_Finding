#include "Actor.h"

void Actor::Update()
{
	//pos += Vec3(1,0,0);

}

void Actor::SetPos(Vec3 pos_)
{
	pos = pos_;
}

void Actor::Render()
{

	SDL_Rect rect;
	Vec3 screenCoords;
	int    w, h;

	screenCoords = scene->getProjectionMatrix() * pos;

	// notice use of "body" in the following
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

	rect.w = static_cast<int>(w * scale);
	rect.h = static_cast<int>(h * scale);
	rect.x = static_cast<int>(screenCoords.x + 0.15 * rect.w);
	rect.y = static_cast<int>(screenCoords.y - 1.15 * rect.h);


	float degres = orientation * 180.0f / M_PI;

	SDL_RenderCopyEx(scene->game->getRenderer(), texture, nullptr, &rect,
		degres, nullptr, SDL_FLIP_NONE);
}
