#ifndef KINEMATIC_H
#define KINEMATIC_H
#include "Vector.h"
#include "SteeringOutput.h"
class Kinematic
{
public:
	MATH::Vec3 position;
	float orientation;
	MATH::Vec3 velocity;
	float rotation;
	void update(SteeringOutput& steering_, float time);
};
#endif

