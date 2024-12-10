#include "StateMachine.h"

#include <unordered_map>

#include "Condition.h"
#include "Character.h"

State::State(STATE name_) : name(name_)
{
}

STATE State::stringToStateEnum(const std::string& stateName)
{
	static const unordered_map<std::string, STATE> stateMap = {
		{"Seek", STATE::SEEK},
		{"Flee", STATE::FLEE},
		{"Patrol", STATE::PATROL},
		{"Arrive", STATE::ARRIVE},
		{"DoNothing", STATE::DO_NOTHING}
	};

	auto it = stateMap.find(stateName);
	if (it != stateMap.end()) {
		return it->second;
	}

	return STATE::DO_NOTHING; // Handle unmatched strings
}

std::list<Transition*> State::GetTransitions()
{
	return transition;
}
	

void State::AddTransition(Transition* transition_)
{
	transition.push_back(transition_);
}

STATE State::GetName()
{
	return name;
}

Transition::Transition(Condition* condition_, State* targetState_): condition(condition_),targetState(targetState_)
{
}

bool Transition::IsTriggered(Character* npc_)
{
	;
	return condition->test(npc_);
}

State* Transition::GetTargetState()
{
	return targetState;
}

void StateMachine::Update(Character* npc)
{
	Transition* triggered = NULL;

	for(Transition* t : currentState->GetTransitions())
	{
		if(t->IsTriggered(npc))
		{
			triggered = t;
			break;
		}
	}
	if(triggered)
	{
		State* targetState = triggered->GetTargetState();
		currentState = targetState;
		return;
	}
	return;
}

STATE StateMachine::GetCurrentStateName()
{
	return currentState->GetName();
}

void StateMachine::SetInitialState(State* initial_)
{
	initialState = initial_;
	currentState = initial_;
}
