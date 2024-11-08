#pragma once
#include "Character.h"
#include "KinematicSteeringOutput.h"
#include "Static.h"
#include "Body.h"
class KinematicSeek
{
private:
	Body* character;
	Body* target;
	float max_Speed;
	KinematicSteeringOutput* result;
public:
	KinematicSeek(Body* character,Body* target);
	KinematicSteeringOutput* GetSteering();
	float newOrientation(float orientation_, Vec3& vel);
};

