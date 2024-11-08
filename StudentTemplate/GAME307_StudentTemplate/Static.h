#ifndef STATIC_H
#define STATIC_H
#include <Vector.h>


#include "KinematicSteeringOutput.h"
class Static
{
public:
	MATH::Vec3 position;
	float orientaion;
	void update(KinematicSteeringOutput& steering, float deltaTime_);
};
#endif
