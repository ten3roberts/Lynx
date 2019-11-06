#pragma once
// Namespace for generating random values, arrays, and vectors. No arguments yields a result between 0 and 1
struct Vector2;
struct Vector3;
struct Vector4;
#include <random>
namespace Random
{
	// Returns a random int between min and max. returns min >= x < max
	inline static int Integer(int min, int max) { return std::rand() % (max - min) + min; }

	// Returns a random scalar between 0 and 1
	inline static float Rand01() { return (float)std::rand() / RAND_MAX; }

	// Returns a random scalar between -1 and 1
	inline static float RandNorm() { return ((float)std::rand() / RAND_MAX) * 2 - 1; }

	// Returns a random scalar between $min and $max
	inline static float InRange(float min, float max) { return ((float)std::rand() / RAND_MAX) * (max - min) + min; }

	// Generates a random vector<float> list between min and max
	inline std::vector<float> List(unsigned int size, float min, float max)
	{
		std::vector<float> result(size);
		for (unsigned int i = 0; i < size; i++)
			result[i] = ((float)std::rand() / RAND_MAX) * (max - min) + min;
		return result;
	}

	// Generates a random vector<float> list between 0 and 1
	inline std::vector<float> List(unsigned int size)
	{
		std::vector<float> result(size);
		for (unsigned int i = 0; i < size; i++)
			result[i] = (float)std::rand() / RAND_MAX;
		return result;
	}

	// Vector math

	// Will return a vector to a random point on a circle's edge
	Vector2 OnCircle(float radius = 1);

	// Will return a vector with a random direction and magnitude. (Equal chance for each magnitude; sparser further out)
	Vector2 InCircle(float outerRadius, float innerRadius = 0);
	Vector2 InCircle();

	// Will return a vector to a random point on a circle's surface. (Unequal chance for each magnitude; even spread throughout whole sphere)
	Vector2 InCircleEven(float outerRadius, float innerRadius = 0);

	// Unit circle
	Vector2 InCircleEven();

	// Will return a vector to a random point on a sphere
	Vector3 OnSphere(float radius = 1);

	// Will return a vector to a random point on a sphere
	Vector3 OnSphere(float radius, unsigned int seed);

	// Will return a a vector with a random direction and magnitude. (Equal chance for each magnitude; sparser further out)
	Vector3 InSphere(float outerRadius, float innerRadius = 0);
	Vector3 InSphere();

	// Will return a vector to a random point inside a sphere. (Unequal chance for each magnitude; even spread throughout whole sphere)
	Vector3 InSphereEven(float outerRadius, float innerRadius = 0);
	Vector3 InSphereEven();

	Vector3 InCube(float width);
}