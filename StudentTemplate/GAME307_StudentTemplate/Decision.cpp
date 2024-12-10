#include "Decision.h"

DecisionTreeNode* Decision::GetBranch()
{
	if(TestValue())
	{
		return trueNode;
	}
	else
	{
		return falseNode;
	}
	
	
}

DecisionTreeNode* Decision::MakeDecision()
{
	DecisionTreeNode* branch =  GetBranch();
	return branch->MakeDecision();
}
