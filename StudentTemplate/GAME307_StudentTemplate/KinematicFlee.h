#pragma once
#include "Body.h"
#include "KinematicSteeringOutput.h"


class KinematicFlee
{
private:
	Body* character;
	Body* target;
	float max_Speed;
	KinematicSteeringOutput* result;
public:
	KinematicFlee(Body* character, Body* target);
	KinematicSteeringOutput* getSteering();
	float newOrientation(float orientation_, MATH::Vec3& vel);
};

