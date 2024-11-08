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

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	/*image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);*/
	

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png") )
	{
		return false;
	}
	
	// end of character set ups

	///// NPC STUFF //////
	Vec3 pos = Vec3(10.0f,10.0f,00.0f);
	float ori = 0.0f;
	float maxSpeed = 2.0f;
	float maxRot = 7.0f;
	NPC = new StaticBody(pos, ori, maxSpeed, maxRot);

	SDL_Surface* imgNPC  = IMG_Load("Blinky.png");
	SDL_Texture* textureNPC = SDL_CreateTextureFromSurface(renderer,imgNPC);

	if(textureNPC == nullptr)
	{
		return false;
	}
	NPC->setTexture(textureNPC);
	SDL_FreeSurface(imgNPC);


	return true;
}

void Scene1::OnDestroy() 
{
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
	
}

void Scene1::renderNPC(const float scale) const
{
	SDL_Renderer* renderer = game->getRenderer();
	

	SDL_Rect rect;
	Vec3 screenCoords;
	int    w, h;

	screenCoords = projectionMatrix * NPC->getPos();

	// notice use of "body" in the following
	SDL_QueryTexture(NPC->getTexture(), nullptr, nullptr, &w, &h);

	rect.w = static_cast<int>(w * scale);
	rect.h = static_cast<int>(h * scale);
	rect.x = static_cast<int>(screenCoords.x-0.5 * rect.w);
	rect.y= static_cast<int>(screenCoords.y - 0.5 * rect.h);


	// Convert character orientation from radians to degrees.
	float orientation = NPC->getOrientation() ;
	float degres = orientation * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, NPC->getTexture(), nullptr, &rect,
		degres, nullptr, SDL_FLIP_NONE);
}




void Scene1::Update(const float deltaTime) {
	KinematicSteeringOutput* steering;
	KinematicSeek* find = new KinematicSeek(NPC, game->getPlayer());
	KinematicWander* steeringAlgo = new KinematicWander(NPC, game->getPlayer());;
	
	if(VMath::distance(NPC->getPos() , game->getPlayer()->getPos())> 5.0f )
	{
		steering = steeringAlgo->GetSteering();
	}
	else
	{
		steering = find->GetSteering();
	}
	
	NPC->Update(deltaTime, steering);
	// Calculate and apply any steering for npc's
	blinky->Update(deltaTime);


	// Update player
	game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	renderNPC(0.10f);

	// render any npc's
	blinky->render(0.15f);

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed

	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
