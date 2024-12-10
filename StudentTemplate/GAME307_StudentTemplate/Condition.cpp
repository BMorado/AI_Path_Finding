#include "Condition.h"

#include <VMath.h>

#include "Character.h"

Condition::Condition()
{
}

ConditionOutOfRange::ConditionOutOfRange()
{
}

bool ConditionOutOfRange::test(Character* npc)
{
	float threshold = 5.0f;
	if(MATH::VMath::distance(npc->GetPlayerPos(),npc->getStaticBody()->getPos())> threshold)
	{
		return true;
	}
	return false;
}

ConditionInRange::ConditionInRange()
{
}

bool ConditionInRange::test(Character* npc)
{
	float threshold = 5.0f;
	if (MATH::VMath::distance(npc->GetPlayerPos(), npc->getStaticBody()->getPos()) <= threshold && npc->GetHealth()>=1)
	{
		std::cout << "here\n";
		return true;
	}
	return false;
}

ConditionFlee::ConditionFlee()
{
}

bool ConditionFlee::test(Character* npc)
{
	float threshold = 5.0f;
	if (VMath::distance(npc->GetPlayerPos(), npc->getStaticBody()->getPos()) <= threshold && npc->GetHealth()<1)
	{

		return true;
	}
	return false;
}

