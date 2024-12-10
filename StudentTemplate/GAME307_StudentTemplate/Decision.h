#pragma once
#include "DecisionTreeNode.h"
class Decision:
	public DecisionTreeNode
{
protected:
	DecisionTreeNode* trueNode;
	DecisionTreeNode* falseNode;
	class Character* owner;
	virtual DecisionTreeNode* GetBranch();
public:
	Decision() : trueNode(nullptr), falseNode(nullptr),owner(nullptr){}
	Decision(DecisionTreeNode* trueNode_, DecisionTreeNode* falseNode_, Character* owner_):
	trueNode(trueNode_),
	falseNode(falseNode_),
	owner(owner_)
	{}
	virtual bool TestValue() = 0;
	virtual DecisionTreeNode* MakeDecision();
};

