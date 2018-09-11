#include "Random.h"
#include <stdlib.h>

float Random::GetFloat(float max)
{
	return ((float)rand()/RAND_MAX) * max;
}

float Random::GetFloat(float min, float max)
{
	float diff = max - min;
	return (min + GetFloat(diff));
}
