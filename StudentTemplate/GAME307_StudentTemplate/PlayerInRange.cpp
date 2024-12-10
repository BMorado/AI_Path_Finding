#include "PlayerInRange.h"

using namespace MATH;
#include "Character.h"

bool PlayerInRange::TestValue()
{
	if(VMath::distance(owner->getStaticBody()->getPos(),owner->GetPlayerPos()) < 5.0f)
	{
		return true;
	}
	return false;
}
