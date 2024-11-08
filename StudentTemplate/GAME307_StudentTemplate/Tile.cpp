#include "Tile.h"
#include <SDL.h>
#include <SDL_image.h>
Tile::Tile(Vec3 pos_, float width_, float height_, Scene* scene_):pos{pos_},width{width_},height(height_),scene(scene_)
{
}

Tile::~Tile()
{
}

void Tile::Render()
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	const Matrix4 projectionMatrix = scene->getProjectionMatrix();
	SDL_Rect rect;

	Vec3 topLeft, bottomright;
	Vec3 topLeftScreen, bottomRightScreen;
	topLeft = Vec3(pos.x - 0.5f * width, pos.y + 0.5f * height, 0.0f);
	bottomright = Vec3(pos.x + 0.5f * width, pos.y - 0.5f * height, 0.0f);

	topLeftScreen = projectionMatrix * topLeft;
	bottomRightScreen = projectionMatrix * bottomright;
	rect = {
		static_cast<int>(topLeftScreen.x),
		static_cast<int>(topLeftScreen.y),
		static_cast<int>(bottomRightScreen.x - topLeftScreen.x),
		static_cast<int>(bottomRightScreen.y - topLeftScreen.y),
	};
	//SetRGBA(255, 0, 0, 255);

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);

	//SetRGBA(255, 255, 255, 255);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &rect);

}
