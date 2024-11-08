#pragma once
#include "Character.h"
#include "Scene.h"
#include "Node.h"
#include "Graph.h"
#include "Tile.h"
#include "Actor.h"
class Scene2:public Scene 
{
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	Matrix4 projectionMatrix;
	Matrix4     inverseProjection;

	 Graph* graph;
	std::vector<Node*> sceneNodes;

	int temp = 0;

	Actor* actor;
	std::vector<Vec3> worldPos;
	Tile* singleTile;
	Tile* tileArray[25][15];
	std::vector <Tile*> tileList;
	void CreateTiles();

public:
	Scene2(SDL_Window* sdlWindow, GameManager* game_);
	~Scene2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	void renderNPC(float scale) const;
	void GenerateNewPath();
	bool InBould(int i_,int j_);
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};

