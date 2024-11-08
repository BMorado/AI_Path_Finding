#pragma once
#include "Vector.h"
class KinematicSteeringOutput
{
public:
	MATH::Vec3 velocity;
	float rotation;

	KinematicSteeringOutput();
	KinematicSteeringOutput(MATH::Vec3 velocity_, float rotation_);
};

