// Vector math
// Will return a vector to a random point on a sphere
#include <pch.h>

Vector2 Random::OnCircle(float radius) { return Vector2(Random::RandNorm(), Random::RandNorm()).Normalize() * radius; }

Vector2 Random::InCircle(float outerRadius, float innerRadius)
{
	// Generates a random unit vector
	Vector2 result((2.0f * std::rand() / RAND_MAX) - 1.0f, (2.0f * std::rand() / RAND_MAX) - 1.0f);
	result.Normalize(&result);

	// Scales it with a random length
	float randomLength = (float)std::rand() / RAND_MAX;

	result *= randomLength * (outerRadius - innerRadius) + innerRadius;

	return result;
}

Vector2 Random::InCircle()
{
	// Generates a random unit vector
	Vector2 result((2.0f * std::rand() / RAND_MAX) - 1.0f, (2.0f * std::rand() / RAND_MAX) - 1.0f);
	result.Normalize(&result);

	// Scales it with a random length
	float randomLength = (float)std::rand() / RAND_MAX;

	result *= randomLength;

	return result;
}

Vector2 Random::InCircleEven(float outerRadius, float innerRadius)
{
	Vector2 result((2.0f * std::rand() / RAND_MAX) - 1.0f, (2.0f * std::rand() / RAND_MAX) - 1.0f);

	result.Normalize(&result);

	float randomLength = sqrt(((float)std::rand() / RAND_MAX) / MATH_PI); // Accounting sparser distrobution
	result *= randomLength * (outerRadius - innerRadius) + innerRadius;

	return result;
}

Vector2 Random::InCircleEven()
{
	Vector2 result((2.0f * std::rand() / RAND_MAX) - 1.0f, (2.0f * std::rand() / RAND_MAX) - 1.0f);

	result.Normalize(&result);

	float randomLength = sqrt(((float)std::rand() / RAND_MAX) / MATH_PI); // Accounting sparser distrobution
	result *= randomLength;

	return result;
}

Vector3 Random::OnSphere(float radius)
{
	return Vector3(Random::RandNorm(), Random::RandNorm(), Random::RandNorm()).Normalize() * radius;
}

// Will return a vector to a random point on a sphere
Vector3 Random::OnSphere(float radius, unsigned int seed)
{
	std::srand(seed);
	Vector3 vec(Random::RandNorm(), Random::RandNorm(), Random::RandNorm());
	return vec.Normalize() * radius;
}

// Will return a a vector with a random direction and magnitude. (Equal chance
// for each magnitude; sparser further result)
Vector3 Random::InSphere(float outerRadius, float innerRadius)
{
	// Generates a random unit vector
	Vector3 result((2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f);

	result.Normalize(&result);

	// Scales it with a random length
	float randomLength = (float)std::rand() / RAND_MAX;

	result *= randomLength * (outerRadius - innerRadius) + innerRadius;

	return result;
}

Vector3 Random::InSphere()
{
	// Generates a random unit vector
	Vector3 result((2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f);

	result.Normalize(&result);

	// Scales it with a random length
	float randomLength = (float)std::rand() / RAND_MAX;
	result *= randomLength;

	return result;
}

// Will return a vector to a random point inside a sphere. (Unequal chance for
// each magnitude; even spread throughout whole sphere)
Vector3 Random::InSphereEven(float outerRadius, float innerRadius)
{
	Vector3 result((2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f);

	result.Normalize(&result);

	float randomLength = sqrt(((float)std::rand() / RAND_MAX) / MATH_PI); // Accounting sparser distrobution
	result *= randomLength * (outerRadius - innerRadius) + innerRadius;

	return result;
}

Vector3 Random::InSphereEven()
{
	// Generates a random unit vector
	Vector3 result((2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f,

				   (2.0f * std::rand() / RAND_MAX) - 1.0f);

	result.Normalize(&result);

	float randomLength = sqrt(((float)std::rand() / RAND_MAX) / MATH_PI); // Accounting sparser distrobution
	result *= randomLength;

	return result;
}

Vector3 Random::InCube(float width)
{
	return Vector3(((float)std::rand() / RAND_MAX) * width, ((float)std::rand() / RAND_MAX) * width,
				   ((float)std::rand() / RAND_MAX) * width);
}