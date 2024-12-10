#include "KinematicArrive.h"
KinematicArrive::KinematicArrive(Body* character_, const Vec3& pos)
{
	character = character_;
	target = pos;
	result = new SteeringOutput();
}
SteeringOutput* KinematicArrive::GetSteering()
{

	result->linear = target - character->getPos();
	if(VMath::mag(result->linear)<radius )
	{
		result->linear = Vec3(0.0f, 0.0f, 0.0f);
		return NULL;
	}

	result->linear /= timeToTarget;

	if(VMath::mag(result->linear) > max_Speed)
	{
		result->linear = VMath::normalize(result->linear);
		result->linear *= character->getMaxSpeed();

	}

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
