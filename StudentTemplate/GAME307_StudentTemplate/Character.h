#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "DecisionTreeNode.h"
#include "Scene.h"
#include "KinematicBody.h"
#include "StateMachine.h"
#include "StaticBody.h"


using namespace std;

class Character
{
private:
	class KinematicBody* body;
	KinematicBody* body_;
	class Scene* scene;
	DecisionTreeNode* decisionTree;
	StateMachine* stateMachine;
	bool hasEaten;
	Vec3 homePos;
	

public:
	Character()
	{
		body = NULL;
		scene = NULL;
		decisionTree = NULL;
		stateMachine = NULL;
		hasEaten = false;
		
	}
	int health = 5;
	~Character() {};
	bool isHome = false;
	bool GetHasEaten();
	bool OnCreate(Scene* scene_);
	void OnDestroy();
	bool setTextureWith(string file);
	void Update(float time);
	void HandleEvents(const SDL_Event& event);
	Body* getStaticBody() { return body; }
	void render(float scale = 1.0f) const;
	void setHomePos(Character* homeCharacter) { homePos = homeCharacter->getStaticBody()->getPos(); }
	Vec3 GetHomePos() { return homePos; }
	int GetHealth() const { return health; }
	void SubtractHealth(int health_);
	void AddHealth(int health_);
	Vec3 GetPlayerPos() ;
	void MoveToHome(float deltaTime);
	bool ReadDecisionTreeFile( std::string file_);
	bool ReadStateMachineFromFile(std::string file_);

};

#endif

