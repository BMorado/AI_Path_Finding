#pragma once
#include "Body.h"
#include "KinematicSteeringOutput.h"
#include "StaticBody.h"

class KinematicArrive
{
	StaticBody* character;
	Body* target;
	float max_Speed;
	// satisfaction radius 
	float radius = 0.01f;
	// Time to get to target constant
	float timeToTarget = 0.01f;
	KinematicSteeringOutput* result;
public:
	KinematicArrive(StaticBody* character_, Body* target_);
	KinematicSteeringOutput* GetSteering();
	float NewOrientation(float orientation_, MATH::Vec3& vel);
};

