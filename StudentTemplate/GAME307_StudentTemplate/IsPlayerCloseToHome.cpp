#include "IsPlayerCloseToHome.h"

bool IsPlayerCloseToHome::TestValue()
{
   
        if( MATH::VMath::distance(owner->GetPlayerPos(), owner->GetHomePos()) < 5.0f)
        {
            std::cout << true << "  start  " << '\n';
	        return true;
        }
        std::cout << false << "  start  " << '\n';
    return false;
    
}
