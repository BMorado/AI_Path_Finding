#pragma once
#include "Decision.h"
class FloatDecision:Decision
{
private:
	float minValue,maxValue;
public:
	bool testValue();
};

