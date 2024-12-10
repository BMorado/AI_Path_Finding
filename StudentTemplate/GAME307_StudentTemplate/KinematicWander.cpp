#include "KinematicWander.h"

KinematicWander::KinematicWander(Body* character_, Body* target_)
{
    // Ensure the character and target pointers are not null (optional but good practice)
    character = character_;
    target = target_;
    result = new SteeringOutput();
}

SteeringOutput* KinematicWander::GetSteering()
{
    // Get the orientation and calculate the linear velocity vector
    result->linear = character->getMaxSpeed() * OrientationToVec3();

    // Optionally, print the result if debugging (remove if not needed)
    // result->linear.print();

    // Assign random angular velocity
    result->angular = RandomBinomial() * character->getMaxRotation();
    return result;
}

Vec3 KinematicWander::OrientationToVec3()
{
    // Convert the orientation to a direction vector (assuming radians for the orientation)
    return Vec3(cos(character->getOrientation()), sin(character->getOrientation()), 0.0f);
}

float KinematicWander::RandomBinomial()
{
    // Using a consistent random number generator for better performance and readability
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(-1.0f, 1.0f);  // Random value between -1 and 1

    return static_cast<float>(distr(gen));
}


//
//#include "KinematicWander.h"
//KinematicWander::KinematicWander(Body* character_, Body* target_)
//{
//	character = character_;
//	target = target_;
//	result = new SteeringOutput();
//}
//
//SteeringOutput* KinematicWander::GetSteering()
//{
//
//
//	result->linear = character->getMaxSpeed() * OrientationToVec3();
//	result->linear.print();
//
//	result->angular = RandomBinomial() * character->getMaxRotation();
//	return result;
//}
//Vec3 KinematicWander::OrientationToVec3()
//{
//	return Vec3(cos(character->getOrientation()), sin(character->getOrientation()), 0.0f);
//}
//
//float KinematicWander::RandomBinomial()
//{
//	static std::random_device rd;
//	static std::mt19937 gen(rd());
//	std::uniform_real_distribution<> distr(-1.0, 1.0);
//
//	return static_cast<float>(distr(gen));
//
//
//	/*srand(reinterpret_cast<time_t>(nullptr));
//	return rand() % 1 + -1;*/
//
//}



