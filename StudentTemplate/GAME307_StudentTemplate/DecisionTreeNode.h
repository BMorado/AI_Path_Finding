#pragma once
class DecisionTreeNode
{
public:
	virtual ~DecisionTreeNode() = default;

	virtual DecisionTreeNode* MakeDecision() = 0;
};

