#pragma once
#include <limits.h>
#include "pch.h"

#include <cmath>

#include "Matrix.h"
#include "Quaternion.h"
#include "Vector.h"

#define MATH_PI 3.141593f
#define MATH_E 2.718282f

#define DEG_180 MATH_PI
#define DEG_90 1.570796f
#define DEG_60 0.047198f
#define DEG_45 0.785398f

#define D2R 0.0174533
#define R2D 57.2958

#define KILO 1000
#define MEGA 1000000
#define GIGA 1000000000

#define NANO 1.0 / GIGA
#define MICRO 1.0 / MEGA
#define MILLI 1.0 / KILO

#define MINUTE 60
#define HOUR 3600
#define DAY 86400

namespace Math
{
	// public:
	inline static float logn(float x, float base) { return log(x) / log(base); }

	// Clamps value between min and max
	inline static float Clamp(float value, float min, float max)
	{
		return value > max ? max : value < min ? min : value;
	}

	// Clamps value between 0 and infinity
	inline static float ClampPos(float value) { return value < 0 ? 0 : value; }

	// Clamps value between 0 and negative infinity
	inline static float ClampNeg(float value) { return value > 0 ? 0 : value; }

	// Clamps value between 0 and 1
	inline static float Clamp01(float value) { return value > 1 ? 1 : value < 0 ? 0 : value; }

	inline static float ToRad(float& deg) { return (MATH_PI / 180.0f) * deg; }

	inline static float ToDeg(float& rad) { return (180.0f / MATH_PI) * rad; }

	int getMax(float* elements,
			   int size); // Return the index of the greatest value in elements

	int getMax(std::vector<float> elements);

	int getMax(int n, ...);

	//  Returns the index of the smallest value in elements
	int getMin(float* elements, int size);

	int getMin(std::vector<float> elements);

	int getMin(int n, ...);

	// Will generate a sine wave between two thresholds
	inline float SineWave(float min, float max, float frequency, float t)
	{
		return sinf(t * frequency) / 2 * (max - min) + (max + min) / 2;
	}
	inline float CosineWave(float min, float max, float frequency, float t)
	{
		return cosf(t * frequency) / 2 * (max - min) + (max + min) / 2;
	}

	template <typename I> std::string ToHex(I w, size_t hex_len = sizeof(I) << 1, bool uppercase = true)
	{
		static const char* digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
		std::string rc(hex_len, '0');
		for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
			rc[i] = digits[(w >> j) & 0x0f];
		return rc;
	}

	template <typename I> std::string ToOctal(I w, size_t hex_len = sizeof(I) << 1)
	{
		static const char* digits = "01234567";
		std::string rc(hex_len, '0');
		for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
			rc[i] = digits[(w >> j) & 7];
		return rc;
	}

#pragma region "Vector functions"
	// Vector2
	inline float Dot(const Vector2& a, const Vector2& b) { return Vector2::Dot(a, b); }

	// Returns a vector projected onto an axis
	inline Vector2 Project(const Vector2& vector, const Vector2& axis) { return Vector2::Project(vector, axis); }
	// Returns the length of a vector projected onto an axis
	inline float ProjectFlat(const Vector2& vector, const Vector2& axis) { return Vector2::ProjectFlat(vector, axis); }

	// Linearly interpolates a and b between t
	inline Vector2 Lerp(const Vector2& a, const Vector2& b, float t) { return Vector2::Lerp(a, b, t); }

	// Vector3
	// Calculates the dot product between two vectors
	inline float Dot(const Vector3& a, const Vector3& b) { return Vector3::Dot(a, b); }

	// Returns a vector projected onto an axis
	inline Vector3 Project(const Vector3& vector, const Vector3& axis) { return Vector3::Project(vector, axis); }
	// Returns the length of a vector projected onto an axis
	inline float ProjectFlat(const Vector3& vector, const Vector3& axis) { return Vector3::ProjectFlat(vector, axis); }

	// Returns a vector perpendicular to a and b
	inline Vector3 Cross(const Vector3& a, const Vector3& b) { return Vector3::Cross(a, b); }

	// Returns the vector when the ray has been reflected from the normal
	inline Vector3 Reflect(const Vector3& ray, const Vector3& normal) { return Vector3::Reflect(ray, normal); }

	// Linearly interpolates a and b between t
	inline Vector3 Lerp(const Vector3& a, const Vector3& b, float t) { return Vector3::Lerp(a, b, t); }

	// Spherically interpolates a and b between t
	inline Vector3 Slerp(const Vector3& a, const Vector3& b, float t) { return Vector3::Slerp(a, b, t); }

	// Vector4
	inline float Dot(const Vector4& a, const Vector4& b) { return Vector4::Dot(a, b); }

	// Returns a vector projected onto an axis
	inline Vector4 Project(const Vector4& vector, const Vector4& axis) { return Vector4::Project(vector, axis); }
	// Returns the length of a vector projected onto an axis
	inline float ProjectFlat(const Vector4& vector, const Vector4& axis) { return Vector4::ProjectFlat(vector, axis); }

	// Linearly interpolates a and b between t
	inline Vector4 Lerp(const Vector4& a, const Vector4& b, float t) { return Vector4::Lerp(a, b, t); }
#pragma endregion
}; // namespace Math

// Merge Sorting:
template <typename T> struct Sorter
{
	static void Sort(std::vector<T>& input, Vector3& other, bool (*comp)(T a, T b, Vector3& other))
	{
		MergeSort(input, other, 0, input.size() - 1, comp);
	}

  private:
	static void MergeSort(std::vector<T>& input, Vector3& other, int low, int high,
						  bool (*comp)(T a, T b, Vector3& other))
	{
		if (low < high)
		{
			int middle = (low / 2) + (high / 2);
			MergeSort(input, other, low, middle, comp);
			MergeSort(input, other, middle + 1, high, comp);
			Merge(input, other, low, middle, high, comp);
		}
	}

	static void Merge(std::vector<T>& input, Vector3& other, int low, int middle, int high,
					  bool (*comp)(T a, T b, Vector3& other))
	{
		int left = low;
		int right = middle + 1;
		std::vector<T> tmp;
		tmp.resize((high - low) + 1);
		int tmpIndex = 0;

		while ((left <= middle) && (right <= high))
		{
			if (comp(input[left], input[right], other))
			{
				tmp[tmpIndex] = input[left];
				left = left + 1;
			}
			else
			{
				tmp[tmpIndex] = input[right];
				right = right + 1;
			}
			tmpIndex = tmpIndex + 1;
		}

		if (left <= middle)
		{
			while (left <= middle)
			{
				tmp[tmpIndex] = input[left];
				left = left + 1;
				tmpIndex = tmpIndex + 1;
			}
		}

		if (right <= high)
		{
			while (right <= high)
			{
				tmp[tmpIndex] = input[right];
				right = right + 1;
				tmpIndex = tmpIndex + 1;
			}
		}

		for (int i = 0; i < tmp.size(); i++)
		{
			input[low + i] = tmp[i];
		}
	}
};
