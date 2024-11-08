#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(Body* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
}

KinematicSteeringOutput* KinematicSeek::GetSteering()
{

	result->velocity = target->getPos() - character->getPos();

	result->velocity = VMath::normalize(result->velocity)*character->getMaxSpeed();
	result->rotation = 0.0f;
	//result->velocity *= max_Speed;

	//result->rotation = newOrientation(character->getOrientation(), result->velocity);
	result->velocity.print();
	
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
