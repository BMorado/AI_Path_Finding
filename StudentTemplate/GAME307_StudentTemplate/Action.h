#pragma once
#include "DecisionTreeNode.h"

enum class ACTION_SET
{
	DO_NOTHING,
	SEEK,
	FLEE,
	ARRIVE
};
class Action:
	public DecisionTreeNode
{
private:
	ACTION_SET value;
public:
	Action() :value(ACTION_SET::DO_NOTHING) {}
	Action(ACTION_SET value_) : value(value_){}
	ACTION_SET GetValue() const
	{
		return value;
	}

	DecisionTreeNode* MakeDecision() override 
	{
		return this;
	}
};

