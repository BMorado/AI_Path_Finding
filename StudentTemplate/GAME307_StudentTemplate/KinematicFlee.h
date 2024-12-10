#pragma once
#include "Body.h"
#include "KinematicSteeringOutput.h"
#include "SteeringOutput.h"


class KinematicFlee
{
private:
	Body* character;
	Body* target;
	float max_Speed;
	SteeringOutput* result;
public:
	KinematicFlee(Body* character, Body* target);
	SteeringOutput* getSteering();
	float newOrientation(float orientation_, MATH::Vec3& vel);
};

