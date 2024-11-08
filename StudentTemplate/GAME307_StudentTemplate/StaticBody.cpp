#include "StaticBody.h"

void StaticBody::Update(float deltaTime, const KinematicSteeringOutput* steering_)
{
	Body::Update(deltaTime);

	if(steering_ == nullptr)
	{
		vel = Vec3();
		rotation = 0.0f;
		return;
	}
	vel = steering_->velocity;
	rotation = steering_->rotation;

	if(VMath::mag(vel)>maxSpeed)
	{
		vel = VMath::normalize(vel) * maxSpeed;
	}
	rotation = rotation > maxRotation ? maxRotation : rotation;
}

float StaticBody::newOrientation(float orientation_, Vec3& vel)
{
	if (VMath::mag(vel) > 0)
	{
		return (atan2(vel.x, vel.y));
	}
	return orientation;
}