#pragma once

#include <list>
#include <string>

class Character;

enum class STATE { DO_NOTHING, SEEK, ARRIVE, FLEE, PURSUE, SLEEP, EAT, PATROL };

class Transition;
class Condition;


class State
{
private:
	std::list<Transition*> transition;
	STATE name;
public:
	State(STATE name_);
	std::list<Transition*> GetTransitions();
	void AddTransition(Transition* transition_);
	STATE stringToStateEnum(const std::string& stateName);
	STATE GetName();
	
};

class Transition
{
private:
	Condition* condition;
	State* targetState;
public:
	Transition(Condition* condition_,State* targetState_);
	bool IsTriggered(Character* npc_);
	State* GetTargetState();
};

class StateMachine
{
private:
	State* initialState;
	State* currentState;

public:
	
	void Update(Character* npc);
	STATE GetCurrentStateName();
	void SetInitialState(State* initial_);
};

