#include "math.h"

#define M_PI 3.14159265358979323846

float Math::euclidean_distance(float x, float y)
{
	return sqrtf((x * x) + (y * y));
}