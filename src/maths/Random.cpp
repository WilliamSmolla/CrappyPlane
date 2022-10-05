#include "pch.h"
#include "Random.h"

int Random::Range(int min, int max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}
