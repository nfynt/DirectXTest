#include "Maths.h"

const float Maths::PI = 3.141592654f;
const float Maths::TWO_PI = PI * 2.0f;

float Maths::WrapModulo(float value, float max)
{
	while (value > max)
		value -= max;
	while (value < 0.0f)
		value += max;
	return value;
}

float Maths::WrapModulo(float value, float min, float max)
{
	float diff = max - min;
	while (value > max)
		value -= diff;
	while (value < min)
		value += diff;
	return value;
}
