#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new SteeringOutput();
}

SteeringOutput* KinematicSeek::GetSteering()
{

	result->linear = target->getPos() - character->getPos();

	result->linear = VMath::normalize(result->linear)*character->getMaxSpeed();
	result->angular = 0.0f;
	//result->velocity *= max_Speed;

	//result->rotation = newOrientation(character->getOrientation(), result->velocity);

	
	return result;
}
float KinematicSeek::newOrientation(float orientation_, MATH::Vec3& vel)
{
	if(VMath::mag(vel) >0 )
	{
		return (atan2(vel.x, vel.y));
	}
	return orientation_;
	
}
