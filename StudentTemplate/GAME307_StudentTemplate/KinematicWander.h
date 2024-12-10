#pragma once
#include "StaticBody.h"
#include "Body.h"
#include <random>
#include <stdlib.h> 

#include "SteeringOutput.h"

class KinematicWander
{
private:
	Body* character;
	Body* target;
	SteeringOutput* result;
public:
	KinematicWander(Body* character_, Body* target_);
	SteeringOutput* GetSteering();
	Vec3 OrientationToVec3();
	float RandomBinomial();
};

