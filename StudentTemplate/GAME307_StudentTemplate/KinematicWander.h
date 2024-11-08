#pragma once
#include "StaticBody.h"
#include "Body.h"
#include <random>
#include <stdlib.h> 
class KinematicWander
{
private:
	StaticBody* character;
	Body* target;
	KinematicSteeringOutput* result;
public:
	KinematicWander(StaticBody* character_, Body* target_);
	KinematicSteeringOutput* GetSteering();
	Vec3 OrientationToVec3();
	float RandomBinomial();
};

