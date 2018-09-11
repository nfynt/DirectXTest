#ifndef MATHS_H_INCLUDED
#define MATHS_H_INCLUDED

class Maths
{
public:
	static const float PI;
	static const float TWO_PI;
	static float WrapModulo(float value, float max);
	static float WrapModulo(float value, float min, float max);
};

#endif // MATHS_H_INCLUDED
