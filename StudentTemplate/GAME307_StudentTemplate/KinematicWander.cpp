#include "KinematicWander.h"
KinematicWander::KinematicWander(StaticBody* character_, Body* target_)
{
	character = character_;
	target = target_;
	result = new KinematicSteeringOutput();
}

KinematicSteeringOutput* KinematicWander::GetSteering()
{

	
	result->velocity = character->getMaxSpeed() *OrientationToVec3() ;
	result->velocity.print();

	result->rotation = RandomBinomial() * character->getMaxRotation();
	return result;
}
Vec3 KinematicWander::OrientationToVec3()
{
	return Vec3(cos(character->getOrientation()), sin(character->getOrientation()),0.0f);
}

float KinematicWander::RandomBinomial()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> distr(-1.0, 1.0);
	
	return static_cast<float>(distr(gen));


	/*srand(reinterpret_cast<time_t>(nullptr));
	return rand() % 1 + -1;*/
	
}

