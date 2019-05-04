#include "FixedMath.h"

uint16_t randVal = 0xABC;

uint16_t Random()
{
	const uint16_t lsb = (randVal & 1);
	randVal >>= 1;
	
	if (lsb != 0)
		randVal ^= 0xB400u;

	return (randVal - 1);
}