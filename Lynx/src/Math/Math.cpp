#include "Math.h"

#include <pch.h>
#include <stdarg.h> /* va_list, va_start, va_arg, va_end */

#include "Vector3.h"

int Math::getMax(float* elements,
				 int size) // Return the index of the greatest value in elements
{
	int current = 0; //  The current biggest index in elements
	for (int i = 1; i < size; i++)
	{
		if (elements[i] > elements[current])
		{
			current = i;
		}
	}
	return current;
}

int Math::getMax(std::vector<float> elements)
{
	int current = 0; //  The current biggest index in elements
	for (int i = 1; i < elements.size(); i++)
	{
		if (elements[i] > elements[current])
		{
			current = i;
		}
	}
	return current;
}

int Math::getMax(int n, ...)
{
	int i, val, largest;
	va_list vl;
	va_start(vl, n);
	largest = va_arg(vl, int);
	for (i = 1; i < n; i++)
	{
		val = va_arg(vl, int);
		largest = (largest > val) ? largest : val;
	}
	va_end(vl);
	return largest;
}

int Math::getMin(float* elements, int size)
{
	int current = 0; //  The current smallest index in elements
	for (int i = 1; i < size; i++)
	{
		if (elements[i] < elements[current])
		{
			current = i;
		}
	}
	return current;
}

int Math::getMin(int n, ...)
{
	int i, val, largest;
	va_list vl;
	va_start(vl, n);
	largest = va_arg(vl, int);
	for (i = 1; i < n; i++)
	{
		val = va_arg(vl, int);
		largest = (largest > val) ? largest : val;
	}
	va_end(vl);
	return largest;
}

int Math::getMin(std::vector<float> elements)
{
	int current = 0; //  The current biggest index in elements
	for (int i = 1; i < elements.size(); i++)
	{
		if (elements[i] < elements[current])
		{
			current = i;
		}
	}
	return current;
}
