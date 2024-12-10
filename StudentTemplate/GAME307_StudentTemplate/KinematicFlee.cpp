#include "KinematicFlee.h"

#include <VMath.h>

#include "SteeringOutput.h"


KinematicFlee::KinematicFlee(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new SteeringOutput();
}

SteeringOutput* KinematicFlee::getSteering()
{

	result->linear = character->getPos()-target->getPos() ;

	result->linear = MATH::VMath::normalize(result->linear) * character->getMaxSpeed();
	result->angular = 0.0f;
	//result->velocity *= max_Speed;

	//result->rotation = newOrientation(character->getOrientation(), result->velocity);

	return result;
}
float KinematicFlee::newOrientation(float orientation_, MATH::Vec3& vel)
{
	if (MATH::VMath::mag(vel) > 0)
	{
		return (atan2(vel.x, vel.y));
	}
	return orientation_;

}
