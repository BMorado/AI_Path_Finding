#include "Scene1.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// create a NPC
	blinky = nullptr;
}

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);
	// using this as a simple way to render a sprite and position
	home = new Character();
	if (!home->OnCreate(this) || !home->setTextureWith("Clyde.png"))
	{
		return false;
	}
	home->getStaticBody()->setPos(Vec3(15,7,0));

	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png") )
	{
		
		return false;
	}
	blinky->setHomePos(home);
	blinky->ReadDecisionTreeFile("Near Player");

	inky = new Character();
	if (!inky->OnCreate(this) || !inky->setTextureWith("Inky.png"))
	{
		return false;
	}
	inky->setHomePos(home);
	inky->ReadStateMachineFromFile("StateMachineFile.xml");
	// end of character set ups

	
	



	return true;
}

void Scene1::OnDestroy() 
{
	if (blinky)
	{
		blinky->OnDestroy();
		
		delete blinky;
	}
	if (inky)
	{
		inky->OnDestroy();
		delete inky;
	}
	home->OnDestroy();
	delete home;
	
}

void Scene1::Update(const float deltaTime) {

	blinky->Update(deltaTime);
	inky->Update(deltaTime);
	home->Update(deltaTime);
	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	blinky->render(0.15f);
	home->render(0.15f);
	inky->render(0.15f);

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
	inky->HandleEvents(event);
}
