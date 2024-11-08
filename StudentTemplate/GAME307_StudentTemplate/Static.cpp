#include "Static.h"
void Static::update(KinematicSteeringOutput& steering, float deltaTime_)
{
	position += steering.velocity * deltaTime_;
	orientaion += steering.rotation * deltaTime_;

}
