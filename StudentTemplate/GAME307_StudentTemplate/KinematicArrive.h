#pragma once
#include "Body.h"
#include "KinematicSteeringOutput.h"
#include "StaticBody.h"
#include "SteeringOutput.h"

class KinematicArrive
{
	Body* character;
	Vec3 target;
	float max_Speed;
	// satisfaction radius 
	float radius = 3.0f;
	// Time to get to target constant
	float timeToTarget = 0.01f;
	SteeringOutput* result;
public:
	KinematicArrive(Body* character_,const Vec3& pos);
	SteeringOutput* GetSteering();
	float NewOrientation(float orientation_, MATH::Vec3& vel);
};

