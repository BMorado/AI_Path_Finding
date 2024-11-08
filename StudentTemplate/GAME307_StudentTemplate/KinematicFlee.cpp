#include "KinematicFlee.h"

#include <VMath.h>


KinematicFlee::KinematicFlee(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
}

KinematicSteeringOutput* KinematicFlee::getSteering()
{

	result->velocity = character->getPos()-target->getPos() ;

	result->velocity = MATH::VMath::normalize(result->velocity) * character->getMaxSpeed();
	result->rotation = 0.0f;
	//result->velocity *= max_Speed;

	//result->rotation = newOrientation(character->getOrientation(), result->velocity);
	result->velocity.print();

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
