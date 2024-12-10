#include "IsHealthLow.h"
#include "Character.h"
#include <iostream>

bool IsHealthLow::TestValue()
{
	std::cout << owner->health << "  start  " << '\n';
	if(owner-> GetHealth() < 1)
	{
		std::cout << owner->GetHealth() << "  Low  " << '\n';
		return true;
	}
	std::cout << owner->GetHealth() << "  OVER 1 "<< '\n';
	return false;
}
