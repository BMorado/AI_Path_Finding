#include "FloatDecision.h"

bool FloatDecision::testValue()
{
	if(maxValue >= TestValue() >=minValue)
	{
		return true;
	}
	return false;
}
