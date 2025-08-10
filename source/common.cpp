#include "common.hpp"
float randomFloat(float a, float b)
{
	return (b-a)*(float)(std::rand()) / (float)(RAND_MAX) + a;
}

void testFunc()
{
}
