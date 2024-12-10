#include "Kinematic.h"

#include <VMath.h>

void Kinematic::update(SteeringOutput& steering_, float time)
{
	float half_t_sq = 0.5f * time * time;
	position += velocity * time + steering_.linear * half_t_sq;
	orientation += rotation * time + steering_.angular * half_t_sq;

	
}

