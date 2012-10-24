#include "PhotonParameterizedTest.h"

#define A 1664525
#define B 1013904223
#define N 4294967296

long PP_RANDOM_SEED = 0;

//#include <stdlib.h>

long __PP_Random_Value(long from_inclusive, long to_exclusive, long random_seed) {
	static long x;
	if (PP_RANDOM_SEED != random_seed) {
		PP_RANDOM_SEED = random_seed;
		x = random_seed;
	}
	x = (A*x + B)%N;
	return (x%(to_exclusive-from_inclusive))+from_inclusive;
	//int _random_seed = PP_RANDOM_SEED + random_seed;
	//return _random_seed;
	//srand(_random_seed);
	//return rand();
}

