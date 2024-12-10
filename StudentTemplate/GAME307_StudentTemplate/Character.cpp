#include "Character.h"

#include <unordered_map>

#include "Action.h"
#include "KinematicSeek.h"
#include "KinematicFlee.h"
#include "KinematicWander.h"
#include  "KinematicArrive.h"

#include "PlayerInRange.h"
#include "Condition.h"
#include "IsHealthLow.h"
#include "IsPlayerCloseToHome.h"
#include "StateMachine.h"
#include "tinyxml2.h"
using namespace tinyxml2;

bool Character::GetHasEaten()
{
	return hasEaten;
}

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;

	// Configure and instantiate the body to use for the demo
	if (!body)
	{
		float radius = 0.2;
		float orientation = 0.0f;
		float rotation = 0.0f;
		float angular = 0.0f;
		float maxSpeed = 4.0f;
		float maxAcceleration = 10.0f;
		float maxRotation = 2.0f;
		float maxAngular = 10.0f;
		body = new KinematicBody(
			Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
			radius,
			orientation,
			rotation,
			angular,
			maxSpeed,
			maxAcceleration,
			maxRotation,
			maxAngular
		);
	}

	if (!body)
	{
		return false;
	}


	
	return true;
}

void Character::OnDestroy()
{
	if (body)
	{
		if (body->getTexture())
		{
			SDL_DestroyTexture(body->getTexture());
		}
		delete body;
	}
};

bool Character::setTextureWith(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	if (image == nullptr) {
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	SDL_Window* window = scene->getWindow();
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (!texture) 
	{
		std::cerr << "Can't create texture" << std::endl;
		return false;
	}
	if (body->getTexture()) SDL_DestroyTexture(body->getTexture());
	body->setTexture(texture);
	SDL_FreeSurface(image);
	return true;
}

void Character::Update(float deltaTime)
{
	// create a new overall steering output
	SteeringOutput* steering;
	steering = NULL;
	if(decisionTree)
	{
		DecisionTreeNode* action = decisionTree->MakeDecision();

		switch (dynamic_cast<Action*>(action)->GetValue())
		{
		case ACTION_SET::SEEK:
		{
			KinematicSeek* temp = new KinematicSeek(this->getStaticBody(), scene->game->getPlayer());
			steering = temp->GetSteering();
		}

		break;
		case ACTION_SET::FLEE:
		{
			KinematicFlee* flee = new KinematicFlee(this->getStaticBody(), scene->game->getPlayer());
			steering = flee->getSteering();
		}

		break;
		case ACTION_SET::ARRIVE:
			break;
		case ACTION_SET::DO_NOTHING:
			KinematicArrive* arrive = new KinematicArrive(this->getStaticBody(), homePos);
			steering = arrive->GetSteering();
			break;
		case ACTION_SET::TAUNT:
			std::cout << "Come here and try and get me \n";
			break;
		}
	}
	if(stateMachine)
	{
		stateMachine->Update(this);
		switch (stateMachine->GetCurrentStateName())
		{
		case STATE::DO_NOTHING:
			std::cout << "State Do Nothing \n";
			break;
		case STATE::FLEE:
			{
				KinematicFlee* flee = new KinematicFlee(this->getStaticBody(), scene->game->getPlayer());
				steering = flee->getSteering();
				std::cout << "State Fleeing \n";
			}
			break;
		case STATE::SEEK:
			{
			KinematicSeek* temp = new KinematicSeek(this->getStaticBody(), scene->game->getPlayer());
			steering = temp->GetSteering();
			std::cout << "State Seeking \n";
			}
			break;
		case STATE::PATROL:
			KinematicArrive* arrive = new KinematicArrive(this->getStaticBody(), homePos);
			steering = arrive->GetSteering();
			break;
		}
	}
	body->Update(deltaTime, steering);

}

void Character::HandleEvents(const SDL_Event& event)
{

	// if key is released, stop applying movement

	if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
			// This section demonstrates using velocity for player movement
			//
			// Need to always normalize velocity, otherwise if player
			// releases one of two pressed keys, then speed remains at sqrt(0.5) of maxSpeed
		case SDL_SCANCODE_LEFT:
			
			break;
		case SDL_SCANCODE_RIGHT:
			
			break;
		case SDL_SCANCODE_DOWN:
			SubtractHealth(1);
			break;
		case SDL_SCANCODE_UP:
			AddHealth(1);
			break;

		
		default:
			break;
		}
	}
}

void Character::render(float scale) const
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	SDL_Rect square;
	Vec3 screenCoords;
	int    w, h;

	// notice use of "body" in the following
	SDL_QueryTexture(body->getTexture(), nullptr, nullptr, &w, &h);
	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	screenCoords = projectionMatrix * body->getPos();
	square.x = static_cast<int>(screenCoords.x - 0.5f * w);
	square.y = static_cast<int>(screenCoords.y - 0.5f * h);
	square.w = w;
	square.h = h;

	// Convert character orientation from radians to degrees.
	float orientation = body->getOrientation() * 180.0f / M_PI;

	SDL_RenderCopyEx(renderer, body->getTexture(), nullptr, &square,
		orientation, nullptr, SDL_FLIP_NONE);
}

void Character::SubtractHealth(int health_)
{
	if (health > 0)
	{
		 health -= health_;
		 std::cout << health << '\n';
	}
}

void Character::AddHealth(int health_)
{
	health += health_;
	std::cout << health << '\n';
}

Vec3 Character::GetPlayerPos() 
{
	return scene->game->getPlayer()->getPos();
}

void Character::MoveToHome(float deltaTime)
{
	Vec3 direction = homePos - getStaticBody()->getPos();
	float distance = VMath::mag(direction);
	if (distance < 0.1f) {  // 0.1 is an arbitrary small distance threshold
		body->setPos(homePos);  // Directly set the position to the target
		return;
	}
	// Normalize the direction vector to get the unit vector
	direction = VMath::normalize(direction);

	// Move the character towards the target at the specified speed
	Vec3 movement =  (getStaticBody()->getMaxSpeed() * deltaTime)* direction;

	// Update the position of the character
	body->setPos(body->getPos() + movement);
}

bool Character::ReadDecisionTreeFile( std::string file_)
{
	
	if(file_ == "Near Player")
	{

		DecisionTreeNode* chasePlayer = new Action(ACTION_SET::SEEK);     // Chase player
		DecisionTreeNode* flee = new Action(ACTION_SET::FLEE);           // Flee
		DecisionTreeNode* patrol = new Action(ACTION_SET::DO_NOTHING);   // Patrol
		DecisionTreeNode* Taunt = new Action(ACTION_SET::TAUNT); // Do nothing

		decisionTree = new IsHealthLow(flee, chasePlayer, this);
		decisionTree = new PlayerInRange(chasePlayer, patrol, this);
		decisionTree = new IsPlayerCloseToHome(chasePlayer, patrol, this);
		decisionTree = new PlayerInRange(chasePlayer, Taunt, this);
		decisionTree = new IsHealthLow(flee, chasePlayer, this);

		

		

	
		return true;
	}
	return false;
}

bool Character::ReadStateMachineFromFile(std::string file_)
{
		stateMachine = new StateMachine();
		if (!stateMachine)
		{
			return false;
		}
		State* chasePlayer = new State(STATE::SEEK);
		State* patrol = new State(STATE::PATROL);
		State* flee = new State(STATE::FLEE);

		flee->AddTransition(new Transition(new ConditionInRange(), chasePlayer));
		flee->AddTransition(new Transition(new ConditionOutOfRange(), patrol));

		chasePlayer->AddTransition(new Transition(new ConditionFlee(), flee));
		chasePlayer->AddTransition(new Transition(new ConditionOutOfRange(), patrol));
	
		patrol->AddTransition(new Transition(new ConditionInRange(), chasePlayer));
		patrol->AddTransition(new Transition(new ConditionFlee(), flee));

		stateMachine->SetInitialState(chasePlayer);
	
	
	return true;
}


