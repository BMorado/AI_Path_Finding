#include "KinematicArrive.h"
KinematicArrive::KinematicArrive(StaticBody* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
}
KinematicSteeringOutput* KinematicArrive::GetSteering()
{
	result->velocity = target->getPos() - character->getPos();
	if(VMath::mag(result->velocity)<radius )
	{
		return nullptr;
	}

	result->velocity /= timeToTarget;

	if(VMath::mag(result->velocity) > max_Speed)
	{
		result->velocity = VMath::normalize(result->velocity);
		result->velocity *= character->getMaxSpeed();
		character->newOrientation(character->getOrientation(), result->velocity);
	}

	//result->rotation = 0.0f;
	return result;
}
float KinematicArrive::NewOrientation(float orientation_, MATH::Vec3& vel)
{
	if (VMath::mag(vel) > 0)
	{
		return (atan2(vel.x, vel.y));
	}
	return orientation_;
}
